/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "PasswordCommand.hpp"

ftp::PasswordCommand::PasswordCommand()
{
}

void ftp::PasswordCommand::execute(std::string args, Client &client)
{
    if (client.getUsername() == "Anonymous" && args.empty()) {
        dprintf(client.getSocket(), "230 User logged in, proceed.\r\n");
        client.setLoggedIn(true);
    } else if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
    } else if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "332 User logged in, proceed.\r\n");
        client.setLoggedIn(true);
    } else {
        dprintf(client.getSocket(), "530 Already logged in.\r\n");
    }
}