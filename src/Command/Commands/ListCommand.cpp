/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "ListCommand.hpp"

#include <sys/wait.h>

ftp::ListCommand::ListCommand()
{
}

void ftp::ListCommand::execute(std::string args, Client& client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (!client.isActiveMode() && !client.isPassiveMode()) {
        client.sendCustomResponse(425, "Use PORT or PASV first.");
        return;
    }
    int connectionSocket;
    if (client.isActiveMode()) {
        connectionSocket = acceptDataActiveConnection(client);
    } else if (client.isPassiveMode()) {
        connectionSocket = acceptDataPassiveConnection(client);
    }
    if (connectionSocket < 0) {
        client.sendCustomResponse(425, "Cannot open data connection.");
        return;
    }
    std::filesystem::path path;
    if (args.empty()) {
        path = client.getRootPath();
    } else {
        path = client.getRootPath() / args;
    }
    path = std::filesystem::weakly_canonical(path);
    if (!std::filesystem::exists(path) || path.string().find(client.getRootDir().string()) != 0) {
        client.sendCommandResponse(550);
        return;
    }
    client.sendCommandResponse(150);
    pid_t pid = fork();
    if (pid < 0) {
        client.sendCustomResponse(450, "Fork failed.");
        client.resetDataMode();
    } else if (pid == 0) {
        dup2(connectionSocket, STDOUT_FILENO);
        execlp("/bin/ls", "ls", "-l", path.c_str(), nullptr);
        close(connectionSocket);
        _exit(0);
    } else {
        close(connectionSocket);
        waitpid(pid, nullptr, 0);
        client.sendCommandResponse(226);
        client.resetDataMode();
    }
}
