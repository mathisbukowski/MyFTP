/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "UserCommand.hpp"


ftp::UserCommand::UserCommand()
{
}

void ftp::UserCommand::execute(std::string args, Client &client)
{
    if (client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Already logged in.\r\n");
    }
    if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
    }
    if (client.getUsername() == args) {
        dprintf(client.getSocket(), "230 User logged in, proceed.\r\n");
        client.setLoggedIn(true);
    } else {
        dprintf(client.getSocket(), "331 User name okay, need password.\r\n");
    }
}