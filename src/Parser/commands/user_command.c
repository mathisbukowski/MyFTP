/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void user_command(client_t *client, char *args)
{
    if (client->logged_in) {
        dprintf(client->socket, "530 Can't change from guest user.\r\n");
        return;
    }
    if (!args) {
        dprintf(client->socket, "530 Permission denied.\r\n");
        return;
    }
    strcpy(client->username, args);
    dprintf(client->socket, "331 User name okay, need password.\r\n");
}
