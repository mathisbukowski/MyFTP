/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "NoopCommand.hpp"

ftp::NoopCommand::NoopCommand()
{
}

void ftp::NoopCommand::execute(std::string args, Client &client)
{
    (void)args;
    if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Please login with USER and PASS.\r\n");
        return;
    }
    dprintf(client.getSocket(), "200 Command okay.\r\n");
}
