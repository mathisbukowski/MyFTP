/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"
#include <criterion/criterion.h>


Test(server_error, valid_address)
{
    server_t server;
    struct sockaddr_in sin;

    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(21);
    cr_assert_eq(checking_server_error(&server, &sin, "127.0.0.1"), 0);
}


Test(server_error, invalid_address)
{
    server_t server;
    struct sockaddr_in sin;

    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(21);

    cr_assert_eq(checking_server_error(&server, &sin, NULL), 84);
}

Test(server_error, invalid_socket)
{
    server_t server;
    struct sockaddr_in sin;

    server.socket = -1;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(21);

    cr_assert_eq(checking_server_error(&server, &sin, "127.0.0.1"), 84);
}