/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_cwd
*/

#include "ftp.h"
#include <criterion/criterion.h>


Test(cwd_command, test_cwd)
{
    client_t client = { .logged_in = 1, .socket = 42 };
    char args[] = "CWD";

    cwd_command(&client, args);
    cr_assert_eq(client.logged_in, 1, "Client should be logged in");
}

Test(cwd_command, test_cwd_not_logged_in)
{
    client_t client = { .logged_in = 0, .socket = 42 };
    char args[] = "CWD";

    cwd_command(&client, args);
    cr_assert_eq(client.logged_in, 0, "Client should not be logged in");
}

Test(cwd_command, test_cwd_change_directory)
{
    client_t client = { .logged_in = 1, .socket = 42 };
    char args[] = "CWD";

    cwd_command(&client, args);
    cr_assert_eq(chdir(".."), 0, "Directory should be changed");
}