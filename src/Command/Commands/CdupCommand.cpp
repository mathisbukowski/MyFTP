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
    (void)args;
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    std::filesystem::path current = client.getCwd();

    if (current == "/") {
        client.sendCustomResponse(550, "Aleready at root directory.");
        return;
    }
    std::filesystem::path parent = current.parent_path();
    if (parent.string().empty()) {
        parent = "/";
    }
    client.setCwd(parent);
    client.sendCommandResponse(200);
}