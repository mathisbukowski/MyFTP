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
    if (!args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    client.sendCustomResponse(257, "\"" + client.getCwd().string() + "\" is the current directory.");
}