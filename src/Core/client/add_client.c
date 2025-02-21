/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void add_new_client(server_t *server, client_t *new_client)
{
    client_t *last = NULL;

    if (!server || !new_client)
        return;
    last = server->clients;
    while (last->next != server->clients)
        last = last->next;
    last->next = new_client;
    new_client->next = server->clients;
}

void add_client(server_t *server, int client_socket)
{
    client_t *new_client = NULL;

    if (!server)
        return;
    new_client = malloc(sizeof(client_t));
    if (!new_client)
        return;
    new_client->socket = client_socket;
    new_client->data_socket = -1;
    new_client->passive_mode = 0;
    new_client->logged_in = 0;
    memset(new_client->username, 0, sizeof(new_client->username));
    getcwd(new_client->cwd, sizeof(new_client->cwd));
    if (!server->clients) {
        server->clients = new_client;
        new_client->next = new_client;
    } else
        add_new_client(server, new_client);
}
