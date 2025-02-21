/*
** EPITECH PROJECT, 2025
** test
** File description:
** command
*/

#include "ftp.h"


void test_command(client_t *client, char *args)
{
    (void)args;
    write(client->socket, "200 Command okay.\r\n",
        sizeof("200 Command okay.\r\n"));
}
