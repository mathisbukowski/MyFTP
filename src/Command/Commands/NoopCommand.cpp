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
    dprintf(client.getSocket(), "200 Command okay.\r\n");
}
