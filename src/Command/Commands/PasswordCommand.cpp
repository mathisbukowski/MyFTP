/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "PasswordCommand.hpp"

ftp::PasswordCommand::PasswordCommand()
{
}

void ftp::PasswordCommand::execute(std::string args, Client &client)
{
    if (client.isLoggedIn()) {
        client.sendCustomResponse(530, "Already logged in.");
        return;
    }
    if (client.getUsername().empty()) {
        client.sendCommandResponse(332);
        return;
    }
    if (client.getUsername() == "Anonymous") {
        if (args.empty()) {
            client.sendCommandResponse(230);
            client.setLoggedIn(true);
            return;
        }
        client.sendCustomResponse(530, "Anonymous user cannot have a password.");
        return;
    }
    if (args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    client.setLoggedIn(true);
    client.sendCommandResponse(230);
}
