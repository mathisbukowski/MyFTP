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
    dprintf(client.getSocket(), "221 Service closing control connection.\r\n");
    _server.handleClientDisconnection(_server._fds, &_server._nfds, client.getSocket(), true);
}