/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "PortCommand.hpp"

ftp::PortCommand::PortCommand()
{
}

void ftp::PortCommand::execute(std::string args, Client &client)
{
    std::vector<std::string> ipAndPort = split(args, ',');
    if (ipAndPort.size() != 6) {
        dprintf(client.getSocket(), "500 Syntax error, command unrecognized.\r\n");
        return;
    }
    std::string ip = ipAndPort[0] + "." + ipAndPort[1] + "." + ipAndPort[2] + "." + ipAndPort[3];
    int port = std::stoi(ipAndPort[4]) * 256 + std::stoi(ipAndPort[5]);
    client.setDataAddr(createAddr(ip, port));
    client.setPassiveMode(false);
    dprintf(client.getSocket(), "200 Command okay.\r\n");
}

sockaddr_in ftp::PortCommand::createAddr(const std::string &ip, int port)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
    return addr;
}

std::vector<std::string> ftp::PortCommand::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}