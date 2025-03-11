/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "StorCommand.hpp"

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
    std::ofstream file(args, std::ios::binary);
    if (!file.is_open()) {
        client.sendCustomResponse(450, "Cannot open file.");
        return;
    }
    char buffer[4096];
    ssize_t bytesRead;
    while ((bytesRead = read(connectionSocket, buffer, sizeof(buffer))) > 0) {
        file.write(buffer, bytesRead);
    }
    if (bytesRead == 0) {
        client.sendCommandResponse(226);
    } else if (bytesRead < 0) {
        client.sendCommandResponse(450);
    }
    file.close();
    close(connectionSocket);
    close(client.getDataSocket());
    client.resetDataMode();
}