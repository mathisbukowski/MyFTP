/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_user
*/

#include <criterion/criterion.h>
#include "ftp.h"

Test(user_command, test_user)
{
    client_t client = { .logged_in = 0, .socket = 42 };
    char args[] = "USER";

    user_command(&client, args);
    cr_assert_eq(client.logged_in, 0, "Client should not be logged in");
}

Test(user_command, test_user_not_logged_in)
{
    client_t client = { .logged_in = 1, .socket = 42 };
    char args[] = "USER";

    user_command(&client, args);
    cr_assert_eq(client.logged_in, 1, "Client should be logged in");
}

Test(user_command, test_args)
{
    client_t client = { .logged_in = 0, .socket = 42 };

    user_command(&client, NULL);
    cr_assert_eq(client.logged_in, 0, "Client should not be logged in");
}

