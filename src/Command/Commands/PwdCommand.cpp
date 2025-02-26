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
    dprintf(client.getSocket(), "257 \"%s\" created.\r\n", client.getCwd().c_str());
}