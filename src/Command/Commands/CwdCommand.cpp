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
    std::filesystem::path newPath = client.getRootPath() / args;
    newPath = std::filesystem::weakly_canonical(newPath);
    if (!std::filesystem::exists(newPath) || !std::filesystem::is_directory(newPath)) {
        client.sendCommandResponse(550);
        return;
    }
    client.setCwd("/" + args);
    client.sendCommandResponse(250);
}