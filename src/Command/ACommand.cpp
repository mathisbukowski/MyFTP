/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ACommand.hpp"

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

int ftp::ACommand::acceptDataActiveConnection(Client& client)
{
    int connectionSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectionSocket < 0)
        return -1;
    sockaddr_in dataAddr = client.getDataAddr();
    if (connect(connectionSocket, reinterpret_cast<sockaddr *>(&dataAddr), sizeof(client.getDataAddr())) < 0) {
        close(connectionSocket);
        return -1;
    }
    return connectionSocket;
}

int ftp::ACommand::acceptDataPassiveConnection(Client& client)
{
    sockaddr_in dataAddr = client.getDataAddr();
    socklen_t dataAddrSize = sizeof(dataAddr);
    int connectionSocket = accept(client.getDataSocket(), reinterpret_cast<sockaddr *>(&dataAddr), (&dataAddrSize));
    if (connectionSocket < 0)
        return -1;
    return connectionSocket;
}


