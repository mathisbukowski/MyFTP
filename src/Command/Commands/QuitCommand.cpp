/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "QuitCommand.hpp"

ftp::QuitCommand::QuitCommand(Server &server) : _server(server)
{
}

void ftp::QuitCommand::execute(std::string args, Client &client)
{
    (void)args;
    client.sendCommandResponse(221);
    _server.handleClientDisconnection(client.getSocket());
}