/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void password_command(client_t *client, char *args)
{
    (void)args;
    if (!args) {
        dprintf(client->socket, "500 Missing arguments.\r\n");
        return;
    }
    client->logged_in = 1;
    dprintf(client->socket, "332 User logged in, proceed.\r\n");
}
