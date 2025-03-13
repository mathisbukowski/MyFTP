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
    std::filesystem::path newCwd = client.getCwd() / args;
    std::filesystem::path newRootPath = client.getRootPath() / args;
    newCwd = std::filesystem::weakly_canonical(newCwd);
    newRootPath = std::filesystem::weakly_canonical(newRootPath); 

    if (newRootPath.string().find(client.getRootDir().string()) != 0) {
        client.sendCustomResponse(550, "Already at root directory.");
        return;
    }
    if (!std::filesystem::exists(newRootPath) || !std::filesystem::is_directory(newRootPath)) {
        client.sendCommandResponse(550);
        return;
    }
    client.setCwd(newCwd);
    client.setRootPath(newRootPath);
    client.sendCommandResponse(250);
}   