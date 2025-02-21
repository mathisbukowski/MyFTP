/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"


client_t *find_last(server_t *server)
{
    client_t *last = NULL;

    if (!server || !server->clients)
        return NULL;
    last = server->clients;
    while (last->next != server->clients)
        last = last->next;
    return last;
}

void remove_or_update_list(server_t *server, client_t *curr, client_t *prev)
{
    client_t *last = NULL;

    if (!server || !curr)
        return;
    if (curr->next == curr) {
        free(curr);
        server->clients = NULL;
        return;
    }
    if (curr == server->clients) {
        last = find_last(server);
        server->clients = curr->next;
        last->next = server->clients;
    } else {
        prev->next = curr->next;
    }
    free(curr);
}

void remove_client(server_t *server, int client_socket)
{
    client_t *curr = NULL;
    client_t *prev = NULL;

    if (!server || !server->clients)
        return;
    curr = server->clients;
    while (curr != server->clients || prev == NULL) {
        if (curr->socket == client_socket) {
            remove_or_update_list(server, curr, prev);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void delete_all_clients(server_t *server)
{
    client_t *curr = NULL;
    client_t *next;

    if (!server || !server->clients)
        return;
    curr = server->clients;
    while (curr != server->clients) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    server->clients = NULL;
}
