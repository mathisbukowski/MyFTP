/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "StorCommand.hpp"

ftp::StorCommand::StorCommand()
{
}

void ftp::StorCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    if (!client.isActiveMode() && !client.isPassiveMode()) {
        client.sendCustomResponse(425, "Use PORT or PASV first.");
        return;
    }

    std::filesystem::path file_path = client.getCwd() / args;
    try {
        file_path = weakly_canonical(file_path);
        if (file_path.string().find(client.getCwd().string()) != 0) {
            client.sendCommandResponse(550);
            return;
        }
    } catch (const std::filesystem::filesystem_error&) {
        client.sendCommandResponse(550);
        return;
    }

}