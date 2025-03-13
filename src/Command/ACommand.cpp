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

void ftp::ACommand::readAndWriteDataInServer(int connectionSocket, std::ofstream &file, Client &client)
{
    char buffer[4096];
    ssize_t bytesRead;
    while ((bytesRead = read(connectionSocket, buffer, sizeof(buffer))) > 0) {
        file.write(buffer, bytesRead);
    }
    if (bytesRead < 0) {
        client.sendCommandResponse(426);
    }
}

void ftp::ACommand::readAndWriteDataInClient(int connectionSocket, std::ifstream &file, Client &client)
{
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        ssize_t bytesRead = file.gcount();
        if (bytesRead > 0) {
            ssize_t bytesWritten = write(connectionSocket, buffer, bytesRead);
            if (bytesWritten < 0) {
                client.sendCommandResponse(426);
                break;
            }
        }
    }
}