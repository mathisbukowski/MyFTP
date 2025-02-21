/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_password
*/


#include <criterion/criterion.h>
#include "ftp.h"

Test(password_command, test_password)
{
    client_t client = { .logged_in = 0, .socket = 42 };
    char args[] = "PASS";

    password_command(&client, args);
    cr_assert_eq(client.logged_in, 1, "Client should be logged in");
}

Test(password_command, test_password_not_logged_in)
{
    client_t client = { .logged_in = 1, .socket = 42 };
    char args[] = "PASS";

    password_command(&client, args);
    cr_assert_eq(client.logged_in, 1, "Client should be logged in");
}