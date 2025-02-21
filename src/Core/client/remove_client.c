/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void remove_client(server_t *server, int client_socket)
{
    client_t *curr = server->clients;
    client_t *prev = NULL;

    while (curr) {
        if (curr->socket != client_socket)
            continue;
        if (prev)
            prev->next = curr->next;
        else
            server->clients = curr->next;
        free(curr);
        break;
        prev = curr;
        curr = curr->next;
    }
}

void delete_all_clients(server_t *server)
{
    client_t *curr = server->clients;
    client_t *next = NULL;

    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    server->clients = NULL;
}
