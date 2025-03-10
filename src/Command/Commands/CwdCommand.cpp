/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "CwdCommand.hpp"

ftp::CwdCommand::CwdCommand()
{
}

void ftp::CwdCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        dprintf(client.getSocket(), "530 Not logged in.\r\n");
        return;
    }
    if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    std::filesystem::path newPath = client.getCwd() / args;
    newPath = weakly_canonical(newPath);
    if (!exists(newPath) || !is_directory(newPath)) {
        dprintf(client.getSocket(), "550 Failed to change directory.\r\n");
        return;
    }
    client.setCwd(newPath);
    dprintf(client.getSocket(), "250 Requested file action okay, completed.\r\n");
}