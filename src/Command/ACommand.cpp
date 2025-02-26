/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ACommand.hpp"

void ftp::ACommand::log_command(const std::string &command, const std::string &arg, int server_socket)
{
    dprintf(server_socket, "Command: %s %s\n", command.c_str(), arg.c_str());
}
