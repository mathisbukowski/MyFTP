/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_handle_commands
*/


#include "ftp.h"
#include <criterion/criterion.h>

Test(handle_commands, test_user_command)
{
    client_t client = { .logged_in = 0, .socket = 42 };
    char command[] = "USER test";

    handle_commands(&client, command);
    cr_assert_eq(client.logged_in, 0, "Client should not be logged in");
}

Test(handle_commands, test_not_found)
{
    client_t client = { .logged_in = 0, .socket = 42 };
    char command[] = "NOT_FOUND";

    handle_commands(&client, command);
    cr_assert_eq(client.logged_in, 0, "Client should not be logged in");
}