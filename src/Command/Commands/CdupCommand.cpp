/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "CdupCommand.hpp"

ftp::CdupCommand::CdupCommand()
{
}

void ftp::CdupCommand::execute(std::string args, Client &client)
{
    if (!args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    std::filesystem::path currentCwd = client.getCwd();
    std::filesystem::path currentRootPath = client.getRootPath();

    if (currentCwd == "/") {
        client.sendCustomResponse(550, "Already at root directory.");
        return;
    }
    std::filesystem::path currentParent = currentCwd.parent_path();
    std::filesystem::path rootPathParent = currentRootPath.parent_path();

    currentParent = std::filesystem::weakly_canonical(currentParent);
    rootPathParent = std::filesystem::weakly_canonical(rootPathParent);
    if (rootPathParent.string().find(client.getRootDir()) != 0) {
        client.sendCommandResponse(550);
        return;
    }
    client.setCwd(currentParent);
    client.setRootPath(rootPathParent);
    client.sendCommandResponse(200);
}