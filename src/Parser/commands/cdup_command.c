/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

void cdup_command(client_t *client, char *args)
{
    (void)args;
    if (!client->logged_in) {
        dprintf(client->socket, "530 Please login with USER and PASS.\r\n");
        return;
    }
    if (chdir("..") == -1) {
        dprintf(client->socket, "550 Failed to change directory.\r\n");
        return;
    }
    getcwd(client->cwd, sizeof(client->cwd));
    dprintf(client->socket, "250 Directory successfully changed.\r\n");
}
