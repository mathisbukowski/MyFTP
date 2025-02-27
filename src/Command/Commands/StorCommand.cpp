/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "StorCommand.hpp"

ftp::StorCommand::StorCommand()
{
}

void ftp::StorCommand::execute(std::string args, ftp::Client &client)
{
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
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        dprintf(client.getSocket(), "550 Failed to open file.\r\n");
        return;
    }
    dprintf(client.getSocket(), "150 File status okay; about to open data connection.\r\n");
    char buffer[1024];
    int n;
    while ((n = read(client.getDataSocket(), buffer, sizeof(buffer))) > 0) {
        file.write(buffer, n);
    }
    file.close();
    close(client.getDataSocket());
    client.setDataSocket(-1);
    dprintf(client.getSocket(), "226 Closing data connection.\r\n");
}
