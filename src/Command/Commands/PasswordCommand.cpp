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
    if (client.getUsername() == "anonymous" && args.empty()) {
        dprintf(client.getSocket(), "230 User logged in, proceed.\r\n");
        client.setLoggedIn(true);
        return;
    }
    if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    if (client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Already logged in.\r\n");
        return;
    }
    if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "230 User logged in, proceed.\r\n");
        client.setLoggedIn(true);
        return;
    }
    dprintf(client.getSocket(), "332 Need account for login.\r\n");
}
