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


void ftp::PasvCommand::sendPassiveModeResponse(Client& client, sockaddr_in& data_address)
{
    in_addr address = data_address.sin_addr;
    unsigned char *ip = reinterpret_cast<unsigned char *>(&address.s_addr);

    int port = htons(data_address.sin_port);
    int p1 = port / 256;
    int p2 = port % 256;

    dprintf(client.getSocket(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", ip[0], ip[1], ip[2], ip[3], p1, p2);
}

sockaddr_in ftp::PasvCommand::getDataAddress(Client& client, int data_socket)
{
    sockaddr_in control;
    socklen_t control_len = sizeof(control);
    if (getsockname(client.getSocket(), reinterpret_cast<sockaddr *>(&control), &control_len) == -1) {
        return {};
    }
    sockaddr_in data_address = {};
    data_address.sin_family = AF_INET;
    data_address.sin_addr.s_addr = control.sin_addr.s_addr;
    data_address.sin_port = 0;
    if (bind(data_socket, reinterpret_cast<sockaddr *>(&data_address), sizeof(data_address)) == -1) {
        return {};
    }
    socklen_t data_address_len = sizeof(data_address);
    if (getsockname(data_socket, reinterpret_cast<sockaddr *>(&data_address), &data_address_len) == -1) {
        return {};
    }
    if (listen(data_socket, 1) == -1) {
        return {};
    }
    return data_address;
}
int ftp::PasvCommand::createDataSocket(Client& client)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (data_socket == -1) {
        return -1;
    }
    return data_socket;
}

void ftp::PasvCommand::execute(std::string args, Client& client)
{
    if (!client.isLoggedIn()) {
        sendResponse(client, "530 Not logged in.\r\n");
        return;
    }
    if (!args.empty()) {
        sendResponse(client, "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    if (client.isPassiveMode()) {
        sendResponse(client, "530 Already in passive mode.\r\n");
        return;
    }
    client.setPassiveMode(true);
    int data_socket = createDataSocket(client);
    if (data_socket == -1) {
        sendResponse(client, "530 Can't open data connection.\r\n");
        return;
    }
    client.setDataSocket(data_socket);
    sockaddr_in data_address = getDataAddress(client, data_socket);
    if (data_address.sin_port == 0) {
        sendResponse(client, "530 Can't open data connection.\r\n");
        return;
    }
    client.setDataAddr(data_address);
    sendPassiveModeResponse(client, data_address);
}
