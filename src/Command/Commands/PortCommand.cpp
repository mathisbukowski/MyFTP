/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "PortCommand.hpp"

ftp::PortCommand::PortCommand()
{
}

void ftp::PortCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (client.isPassiveMode()) {
        client.sendCommandResponse(503);
        return;
    }
    std::vector
}