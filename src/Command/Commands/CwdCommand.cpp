/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "CwdCommand.hpp"

ftp::CwdCommand::CwdCommand()
{
}

void ftp::CwdCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    std::filesystem::path newPath = client.getCwd() / args;
    newPath = weakly_canonical(newPath);
    if (!exists(newPath) || !is_directory(newPath)) {
      client.sendCommandResponse(550);
        return;
    }
    client.setCwd(newPath);
    client.sendCommandResponse(250);
}