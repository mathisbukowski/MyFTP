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
int ftp::PasvCommand::createDataSocket()
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
        client.sendCustomResponse(530, "Not logged in.");
        return;
    }
    if (!args.empty()) {
        client.sendCommandResponse(501);
        return;
    }
    if (client.isPassiveMode()) {
        client.sendCommandResponse(503);
        return;
    }
    client.setPassiveMode(true);
    int data_socket = createDataSocket();
    if (data_socket == -1) {
        client.sendCommandResponse(425);
        return;
    }
    client.setDataSocket(data_socket);
    sockaddr_in data_address = getDataAddress(client, data_socket);
    if (data_address.sin_port == 0) {
        client.sendCommandResponse(425);
        return;
    }
    client.setDataAddr(data_address);
    client.sendPasvResponse();
}
