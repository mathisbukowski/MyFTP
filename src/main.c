/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#include "ftp.h"

void help_flag(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home "
    "directory for the Anonymous user\n");
}

int main(int ac, char **av)
{
    server_t *server = NULL;

    if (ac != 3) {
        help_flag();
        return 84;
    }
    server = init_server(strtol(av[1], NULL, 10), av[2]);
    if (!server)
        return 84;
    if (ftp_server(server) == 84)
        return 84;
    return 0;
}
