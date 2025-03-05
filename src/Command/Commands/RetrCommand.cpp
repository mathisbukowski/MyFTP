/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "RetrCommand.hpp"

ftp::RetrCommand::RetrCommand()
{
}

void ftp::RetrCommand::execute(std::string args, Client &client)
{
    (void)args;
    if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Please login with USER and PASS.\r\n");
        return;
    }
    if (client.getDataSocket() == -1) {
        dprintf(client.getSocket(), "425 Use PASV or PORT first.\r\n");
        return;
    }
    if (client.getCwd().empty()) {
        dprintf(client.getSocket(), "550 Failed to get current directory.\r\n");
        return;
    }
    std::string path = client.getCwd() + "/" + args;
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        dprintf(client.getSocket(), "550 Failed to open file.\r\n");
        return;
    }
    dprintf(client.getSocket(), "150 File status okay; about to open data connection.\r\n");
    char buffer[1024];
    while (file.read(buffer, sizeof(buffer)).gcount() > 0) {
        write(client.getDataSocket(), buffer, file.gcount());
    }
    file.close();
    dprintf(client.getSocket(), "226 Closing data connection.\r\n");
}
