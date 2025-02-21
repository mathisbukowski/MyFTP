/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/


#include "ftp.h"

client_t *find_client(server_t *server, int client_socket)
{
    client_t *curr = server->clients;

    while (curr) {
        if (curr->socket == client_socket)
            return curr;
        curr = curr->next;
    }
    return NULL;
}
