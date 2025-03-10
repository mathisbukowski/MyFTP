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
        dprintf(client.getSocket(), "530 Not logged in.\r\n");
        return;
    }
    std::filesystem::path current = client.getCwd();

    if (current == "/") {
        dprintf(client.getSocket(), "550 Already at root.\r\n");
        return;
    }
    std::filesystem::path parent = current.parent_path();
    if (parent.string().empty()) {
        parent = "/";
    }
    client.setCwd(parent);
    dprintf(client.getSocket(), "200 Command okay.\r\n");
}