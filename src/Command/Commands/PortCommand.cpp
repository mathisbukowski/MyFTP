/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "PortCommand.hpp"

ftp::PortCommand::PortCommand()
{
}

void ftp::PortCommand::execute(std::string args, Client &client)
{
    if (!client.isLoggedIn()) {
        client.sendCommandResponse(530);
        return;
    }
    if (client.isPassiveMode()) {
        client.sendCommandResponse(503);
        return;
    }
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(args);
    while (std::getline(tokenStream, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 6) {
        client.sendCommandResponse(501);
        return;
    }
    std::string ip = tokens[0] + "." + tokens[1] + "." + tokens[2] + "." + tokens[3];
    int port = std::stoi(tokens[4]) * 256 + std::stoi(tokens[5]);
    sockaddr_in dataAddr;
    dataAddr.sin_family = AF_INET;
    dataAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &dataAddr.sin_addr) <= 0) {
        client.sendCommandResponse(501);
        return;
    }
    client.setDataAddr(dataAddr);
    client.setActiveMode(true);
    client.sendCommandResponse(200);
}