/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#include "../include/ftp.hpp"
#include "Server/Server.hpp"

int help_flag()
{
    std::cout << "USAGE: ./myftp port path" << std::endl;
    std::cout << "\tport\tis the port number on which the server socket listens" << std::endl;
    std::cout << "\tpath\tis the path to the home directory for the Anonymous user" << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if (av[1] && strcmp("-help", av[1]) == 0)
        return help_flag();
    if (ac != 3)
        return 84;
    int port = std::stoi(av[1]);
    if (port <= 0 || port > 65535)
        return 84;
    if (!std::filesystem::exists(av[2]))
        return 84;
    ftp::Server server(port, av[2]);
    return server.run();
}
