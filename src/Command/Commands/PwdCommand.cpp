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
    (void)args;
    if (!client.isLoggedIn()) {
        dprintf(client.getSocket(), "530 Not logged in.\r\n");
        return;
    }
    std::filesystem::path current = client.getCwd();
    dprintf(client.getSocket(), "257 \"%s\"\r\n", current.c_str());
}