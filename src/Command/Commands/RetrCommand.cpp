/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** RetrCommand
*/

#include "RetrCommand.hpp"
#include <sys/wait.h>

ftp::RetrCommand::RetrCommand()
{
}


void ftp::RetrCommand::execute(std::string args, Client &client)
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
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        client.sendCustomResponse(450, "Cannot open file.");
        close(connectionSocket);
        return;
    }
    pid_t pid = fork();
    if (pid < 0) {
        client.sendCommandResponse(550);
        return;
    } else if (pid == 0) {
        char buffer[4096];
        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
            ssize_t bytesRead = file.gcount();
            if (bytesRead > 0) {
                ssize_t bytesWritten = write(connectionSocket, buffer, bytesRead);
                if (bytesWritten < 0) {
                    client.sendCommandResponse(450);
                    break;
                }
            }
        }
        file.close();
        close(connectionSocket);
        close(client.getDataSocket());
        client.setDataSocket(-1);
        _exit(0);
    } else {
        close(connectionSocket);
        waitpid(pid, nullptr, 0);
        client.sendCommandResponse(226);
        client.resetDataMode();
    }
}