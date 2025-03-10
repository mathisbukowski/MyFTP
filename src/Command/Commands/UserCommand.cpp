/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "UserCommand.hpp"


ftp::UserCommand::UserCommand()
{
}

void ftp::UserCommand::execute(std::string args, Client &client)
{
    if (args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    if (client.isLoggedIn()) {
        client.sendCustomResponse(530, "Already logged in.");
        return;
    }
    if (client.getUsername().empty()) {
        client.setUsername(args);
        client.sendCommandResponse(331);
    } else if (client.getUsername() == args) {
        client.sendCommandResponse(230);
        client.setLoggedIn(true);
    } else {
        client.sendCustomResponse(530, "Authentication failed.");
    }
}