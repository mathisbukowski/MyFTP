/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "ListCommand.hpp"

ftp::ListCommand::ListCommand()
{
}

void ftp::ListCommand::execute(std::string args, ftp::Client &client)
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
    dprintf(client.getSocket(), "150 File status okay; about to open data connection.\r\n");
    std::string path = client.getCwd();
    std::string command = "ls -l " + path + " | tail -n +2";
    FILE *ls = popen(command.c_str(), "r");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), ls) != NULL) {
        write(client.getDataSocket(), buffer, strlen(buffer));
    }
    pclose(ls);
    close(client.getDataSocket());
    client.setDataSocket(-1);
    dprintf(client.getSocket(), "226 Closing data connection.\r\n");
}
