/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void cwd_command(client_t *client, char *args)
{
    if (!client->logged_in) {
        dprintf(client->socket, "530 Please login with USER and PASS.\r\n");
        return;
    }
    if (!args) {
        dprintf(client->socket, "550 Failed to change directory.\r\n");
        return;
    }
    if (chdir(args) == -1) {
        dprintf(client->socket, "550 Failed to change directory.\r\n");
        return;
    }
    getcwd(client->cwd, sizeof(client->cwd));
    dprintf(client->socket, "250 Directory successfully changed.\r\n");
}
