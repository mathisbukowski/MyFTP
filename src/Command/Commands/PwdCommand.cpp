/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "PwdCommand.hpp"

ftp::PwdCommand::PwdCommand()
{
}

void ftp::PwdCommand::execute(std::string args, Client &client)
{
    (void)args;
    std::string dir = getcwd(NULL, 0);
    dprintf(client.getSocket(), "257 \"%s\" created.\r\n", dir.c_str());
}