/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#include "../include/ftp.hpp"
#include "Server/Server.hpp"

void help_flag()
{
    std::cout << "USAGE: ./myftp port path" << std::endl;
    std::cout << "\tport\tis the port number on which the server socket listens" << std::endl;
    std::cout << "\tpath\tis the path to the home directory for the Anonymous user" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 3) {
        help_flag();
        return 84;
    }
    ftp::Server server(strtol(av[1], NULL, 10), av[2]);
    return server.process();
}
