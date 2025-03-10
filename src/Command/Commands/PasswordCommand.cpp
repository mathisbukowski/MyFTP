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
    if (client.isLoggedIn()) {
        dprintf(client.getSocket(), "530 Already logged in.\r\n");
        return;
    }
    if (client.getUsername().empty()) {
        dprintf(client.getSocket(), "503 Bad sequence of commands.\r\n");
        return;
    }
    if (client.getUsername() == "Anonymous") {
        if (args.empty()) {
            dprintf(client.getSocket(), "230 User logged in, proceed.\r\n");
            client.setLoggedIn(true);
            return;
        }
        dprintf(client.getSocket(), "530 Anonymous login doest not require a password.\r\n");
        return;
    }
    if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error: missing parameter or argument.\r\n");
        return;
    }
    client.setLoggedIn(true);
    dprintf(client.getSocket(), "230 User logged in, proceed.\r\n");
}
