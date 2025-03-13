/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** DeleCommand
*/

#include "DeleCommand.hpp"

ftp::DeleCommand::DeleCommand()
{
}


void ftp::DeleCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    std::filesystem::path path = std::filesystem::current_path() / client.getRootPath() / args;
    if (!std::filesystem::exists(path)) {
        client.sendCommandResponse(550);
        return;
    }
    if (std::filesystem::is_directory(path)) {
        client.sendCommandResponse(550);
        return;
    }
    
    try {
        std::filesystem::remove(path);
        client.sendCommandResponse(250);
    } catch (const std::filesystem::filesystem_error& e) {
        client.sendCommandResponse(550);
    }
}