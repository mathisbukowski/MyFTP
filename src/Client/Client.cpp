/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** Client
*/

#include "Client.hpp"

ftp::Client::Client(int clientSocket)
    : _socket(clientSocket), _logged_in(0), _data_socket(-1), _passive_mode(0), _data_addr({}), _username("")
{
    char buffCwd[1024];
    getcwd(buffCwd, sizeof(buffCwd));
    _cwd = buffCwd;
}

int ftp::Client::getSocket() const
{
    return _socket;
}

void ftp::Client::setSocket(const int socket)
{
    _socket = socket;
}

bool ftp::Client::getLoggedIn() const
{
    return _logged_in;
}

void ftp::Client::setLoggedIn(const bool logged_in)
{
    _logged_in = logged_in;
}

int ftp::Client::getDataSocket() const
{
    return _data_socket;
}

void ftp::Client::setDataSocket(const int data_socket)
{
    _data_socket = data_socket;
}

int ftp::Client::getPassiveMode() const
{
    return _passive_mode;
}

void ftp::Client::setPassiveMode(const int passive_mode)
{
    _passive_mode = passive_mode;
}

sockaddr_in ftp::Client::getDataAddr() const
{
    return _data_addr;
}

void ftp::Client::setDataAddr(const sockaddr_in& data_addr)
{
    _data_addr = data_addr;
}

std::string ftp::Client::getUsername() const
{
    return _username;
}

void ftp::Client::setUsername(const std::string& username)
{
    _username = username;
}

std::string ftp::Client::getCwd() const
{
    return _cwd;
}

void ftp::Client::setCwd(const std::string& cwd)
{
    _cwd = cwd;
}

ftp::Client::~Client()
{
}
