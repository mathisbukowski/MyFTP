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
    std::string new_dir;
    if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Please login with USER and PASS.\r\n");
        return;
    }
    if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    if (chdir(args.c_str()) == -1) {
        dprintf(client.getSocket(), "550 Failed to change directory.\r\n");
        return;
    }
    new_dir = getcwd(NULL, 1024);
    client.setCwd(new_dir);
    dprintf(client.getSocket(), "250 Requested file action okay, completed.\r\n");
}