/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

static void create_new_data_addr(client_t *client, char *ip, int port)
{
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_port = htons(port);
    client->data_addr.sin_addr.s_addr = inet_addr(ip);
    client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
}

void port_command(client_t *client, char *args)
{
    char *ip = strtok(args, ",");
    int port = atoi(strtok(NULL, ",")) * 256 + atoi(strtok(NULL, ","));

    if (!client->logged_in)
        dprintf(client->socket, "530 Please login with USER and PASS.\r\n");
    if (client->passive_mode) {
        close(client->data_socket);
        client->passive_mode = 0;
    }
    if (!args) {
        dprintf(client->socket, "500 Missing arguments.\r\n");
        return;
    }
    create_new_data_addr(client, ip, port);
    if (connect(client->data_socket, (struct sockaddr *)&client->data_addr,
        sizeof(client->data_addr)) == -1) {
        dprintf(client->socket, "425 Can't open data connection.\r\n");
        return;
    }
    dprintf(client->socket, "200 PORT command successful.\r\n");
}
