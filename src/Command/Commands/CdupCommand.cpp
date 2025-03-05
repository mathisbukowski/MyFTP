/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "CdupCommand.hpp"

ftp::CdupCommand::CdupCommand()
{
}

void ftp::CdupCommand::execute(std::string args, Client &client)
{
    char buffCwd[1024];
    (void)args;
    if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Please login with USER and PASS.\r\n");
        return;
    }
    if (chdir("..") == -1) {
        dprintf(client.getSocket(), "550 Failed to change directory.\r\n");
        return;
    }
    if (getcwd(buffCwd, sizeof(buffCwd)) == nullptr) {
        dprintf(client.getSocket(), "550 Failed to get current directory.\r\n");
        return;
    }
    client.setCwd(buffCwd);
    dprintf(client.getSocket(), "200 Command okay.\r\n");
}