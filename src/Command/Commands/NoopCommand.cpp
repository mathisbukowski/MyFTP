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
    if (!args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    client.sendCommandResponse(200);
}
