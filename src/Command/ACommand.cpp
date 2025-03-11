/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ACommand.hpp"

int ftp::ACommand::acceptDataConnection(Client &client)
{
    int dataSocket = client.getDataSocket();
    if (dataSocket < 0)
        return -1;

    sockaddr_in remoteAddr = {};
    socklen_t remoteAddrLen = sizeof(remoteAddr);
    const int connSocket = accept(dataSocket, reinterpret_cast<sockaddr*>(&remoteAddr), &remoteAddrLen);
    if (connSocket < 0)
        return -1;

    return connSocket;
}