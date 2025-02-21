/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#include "ftp.h"

int check_port(int port)
{
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }
    return 0;
}

int check_path(char *path)
{
    if (access(path, F_OK) == -1) {
        fprintf(stderr, "Invalid path\n");
        return 84;
    }
    return 0;
}

server_t *init_server(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server || check_port(port) == 84 || check_path(path) == 84)
        return NULL;
    server->port = port;
    server->socket = 0;
    server->path = strdup(path);
    server->clients = NULL;
    return server;
}

void destroy_server(server_t *server)
{
    if (!server)
        return;
    delete_all_clients(server);
    free(server->path);
    free(server);
}
