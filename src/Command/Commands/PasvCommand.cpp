/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "PasvCommand.hpp"

ftp::PasvCommand::PasvCommand()
{

}


void ftp::PasvCommand::execute(std::string args, Client& client)
{
    if (!client.isLoggedIn()) {
        dprintf(client.getSocket(), "530 Not logged in.\r\n");
        return;
    }
    if (!args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    if (client.isPassiveMode()) {
        dprintf(client.getSocket(), "530 Already in passive mode.\r\n");
        return;
    }
    client.setPassiveMode(true);
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (data_socket == -1) {
        dprintf(client.getSocket(), "530 Can't open data connection.\r\n");
        return;
    }
    sockaddr_in data_addr = {};
    data_addr.sin_family = AF_INET;
    data_addr.sin_addr.s_addr = INADDR_ANY;
    data_addr.sin_port = 0;
    if (bind(data_socket, (sockaddr *)&data_addr, sizeof(data_addr)) == -1) {
        dprintf(client.getSocket(), "530 Can't open data connection.\r\n");
        close(data_socket);
        return;
    }
    socklen_t len = sizeof(data_addr);
    if (getsockname(data_socket, (sockaddr *)&data_addr, &len) == -1) {
        dprintf(client.getSocket(), "530 Can't open data connection.\r\n");
        close(data_socket);
        return;
    }
    if (listen(data_socket, 1) == -1) {
        dprintf(client.getSocket(), "530 Can't open data connection.\r\n");
        close(data_socket);
        return;
    }
    client.setDataSocket(data_socket);
    client.setDataAddr(data_addr);
    unsigned char *addr = (unsigned char *)&data_addr.sin_addr.s_addr;
    unsigned char *port = (unsigned char *)&data_addr.sin_port;
    dprintf(client.getSocket(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
        addr[0], addr[1], addr[2], addr[3], port[0], port[1]);
}
