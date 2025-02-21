/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void quit_command(client_t *client, char *args)
{
    (void)args;
    if (!client->logged_in)
        dprintf(client->socket, "530 Please login with USER and PASS.\r\n");
    dprintf(client->socket, "221 Goodbye.\r\n");
    close(client->socket);
}
