/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** Client
*/

#include "Client.hpp"

ftp::Client::Client(int clientSocket)
    : _socket(clientSocket), _logged_in(false), _data_socket(-1), _passive_mode(false), _active_mode(false), _data_addr({}), _cwd("/")
{
    _commandResponses = {
        {120, "Service ready in nnn minutes."},
        {125, "Data connection already open; transfer starting."},
        {150, "File status okay; about to open data connection."},
        {200, "Command okay."},
        {214, "Help message."},
        {220, "Service ready for new user."},
        {221, "Service closing control connection."},
        {226, "Closing data connection. Requested file action successful."},
        {230, "User logged in, proceed."},
        {250, "Requested file action okay, completed."},
        {331, "User name okay, need password."},
        {332, "Need account for login."},
        {350, "Requested file action pending further information."},
        {425, "Can't open data connection."},
        {450, "Requested file action not taken. File unavailable."},
        {500, "Unknown Command."},
        {501, "Syntax error in parameters or arguments."},
        {502, "Command not implemented."},
        {503, "Bad sequence of commands."},
        {530, "Not logged in."},
        {550, "Requested action not taken. File unavailable."},
        {553, "Requested action not taken. Filename not allowed."}
    };
}

ftp::Client::~Client()
{
}

void ftp::Client::sendCommandResponse(int code) {
    std::string message = std::to_string(code) + " ";

    auto it = _commandResponses.find(code);
    if (it != _commandResponses.end()) {
        message += it->second;
    } else {
        message += "Unknown status.";
    }
    message += "\r\n";
    dprintf(this->getSocket(), "%s", message.c_str());
}

void ftp::Client::sendCustomResponse(int code, const std::string& custom_message)
{
    std::string message = std::to_string(code) + " " + custom_message + "\r\n";
    dprintf(this->getSocket(), "%s", message.c_str());
}

void ftp::Client::sendPasvResponse() {
    sockaddr_in data_addr = this->getDataAddr();
    unsigned char* ip = (unsigned char*)&data_addr.sin_addr.s_addr;
    int port = ntohs(data_addr.sin_port);
    int p1 = port / 256;
    int p2 = port % 256;

    char buffer[100];
    snprintf(buffer, sizeof(buffer),
            "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
            ip[0], ip[1], ip[2], ip[3], p1, p2);
    dprintf(this->getSocket(), "%s", buffer);
}
