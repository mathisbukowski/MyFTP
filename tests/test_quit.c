/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** $
*/

#include "ftp.h"
#include <criterion/criterion.h>

Test(quit_command, test_quit)
{
    client_t client = { .logged_in = 1, .socket = 42 };
    char args[] = "QUIT";

    quit_command(&client, args);
    cr_assert_eq(client.logged_in, 1, "Client should be logged in");
}

Test(quit_command, test_quit_not_logged_in)
{
    client_t client = { .logged_in = 0, .socket = 42 };
    char args[] = "QUIT";

    quit_command(&client, args);
    cr_assert_eq(client.logged_in, 0, "Client should not be logged in");
}