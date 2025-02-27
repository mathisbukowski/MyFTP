/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "PasvCommand.hpp"

ftp::PasvCommand::PasvCommand()
{
}

void ftp::PasvCommand::execute(std::string args, Client &client)
{
    (void)args;
    if (!client.getLoggedIn()) {
        dprintf(client.getSocket(), "530 Please login with USER and PASS.\r\n");
        return;
    }
    client.setPassiveMode(true);
    dprintf(client.getSocket(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
            client.getDataAddr().sin_addr.s_addr & 0xFF,
            (client.getDataAddr().sin_addr.s_addr & 0xFF00) >> 8,
            (client.getDataAddr().sin_addr.s_addr & 0xFF0000) >> 16,
            (client.getDataAddr().sin_addr.s_addr & 0xFF000000) >> 24,
            client.getDataAddr().sin_port & 0xFF,
            (client.getDataAddr().sin_port & 0xFF00) >> 8);
}
