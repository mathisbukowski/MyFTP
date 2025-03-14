/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "StorCommand.hpp"
#include <wait.h>

ftp::StorCommand::StorCommand()
{
}

void ftp::StorCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    if (!client.isActiveMode() && !client.isPassiveMode()) {
        client.sendCustomResponse(425, "Use PORT or PASV first.");
        return;
    }
    int connectionSocket = acceptDataConnection(client);
    if (connectionSocket < 0) {
        client.sendCustomResponse(425, "Cannot open data connection.");
        return;
    }
    client.sendCommandResponse(150);
    std::filesystem::path path = client.getRootPath() / args;
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        client.sendCustomResponse(450, "Cannot open file.");
        return;
    }
    pid_t pid = fork();
    if (pid < 0) {
        client.sendCustomResponse(450, "Fork failed.");
        client.resetDataMode();
    } else if (pid == 0) {
        readAndWriteDataInServer(connectionSocket, file, client);
        file.close();
        close(connectionSocket);
        _exit(0);
    } else {
        waitpid(pid, nullptr, 0);
        client.sendCommandResponse(226);
        client.resetDataMode();
    }
}
