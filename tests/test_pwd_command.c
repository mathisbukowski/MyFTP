/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_pwd_command
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <string.h>
#include "ftp.h"
#include "test_utils.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(pwd_command, nominal_case, .init = redirect_all_stdout)
{
    client_t *client = malloc(sizeof(client_t));
    client->socket = 1;
    client->logged_in = 1;
    char *current_dir = getcwd(NULL, 0);
    char expected[1024];
    snprintf(expected, sizeof(expected), "257 \"%s\" is the current directory.\n", current_dir);
    
    pwd_command(client, NULL);
    cr_assert_stdout_eq_str(expected);
    free(current_dir);
    free(client);
}

Test(pwd_command, malloc_failure, .init = redirect_all_stdout)
{
    client_t *client = malloc(sizeof(client_t));
    should_malloc_fail = 1;
    client->socket = 1;
    client->logged_in = 1;
    pwd_command(client, NULL);
    cr_assert_stdout_eq_str("500 An error occured.\n");
    free(client);
    should_malloc_fail = 0;
}