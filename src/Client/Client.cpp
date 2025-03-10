/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** Client
*/

#include "Client.hpp"

ftp::Client::Client(int clientSocket)
    : _socket(clientSocket), _logged_in(false), _data_socket(-1), _passive_mode(false), _data_addr({})
{
}

ftp::Client::~Client()
{
}
