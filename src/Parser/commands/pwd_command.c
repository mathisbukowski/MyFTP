/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** pwd_command
*/

#include "ftp.h"


void pwd_command(client_t *client, char *args)
{
    char *path = malloc(sizeof(char) * 1024);

    (void)args;
    if (!path) {
        dprintf(client->socket, "500 An error occured.\n");
        return;
    }
    getcwd(path, 1024);
    dprintf(client->socket, "257 \"%s\" is the current directory.\n", path);
    free(path);
}