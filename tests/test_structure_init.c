/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_server_utils
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "ftp.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(check_port, valid_port)
{
    cr_assert_eq(check_port(8080), 0, "The port 8080 should be valid.");
    cr_assert_eq(check_port(1), 0, "The port 1 should be valid.");
    cr_assert_eq(check_port(65535), 0, "The port 65535 should be valid.");
}

Test(check_port, invalid_port, .init = redirect_all_std)
{
    cr_assert_eq(check_port(0), 84, "Port 0 should be invalid.");
    cr_assert_eq(check_port(-1), 84, "Negative port should be invalid.");
    cr_assert_eq(check_port(70000), 84, "Port above 65535 should be invalid.");
}

Test(check_path, valid_path)
{
    cr_assert_eq(check_path("/tmp"), 0, "The path '/tmp' should be valid.");
}

Test(check_path, invalid_path, .init = redirect_all_std)
{
    cr_assert_eq(check_path("/nonexistent_path"), 84, "A nonexistent path should be invalid.");
    cr_assert_stderr_eq_str("Invalid path\n");
}

Test(init_server, valid_initialization)
{
    server_t *server = init_server(8080, "/tmp");

    cr_assert_not_null(server, "The server should be initialized properly.");
    cr_assert_eq(server->port, 8080, "The server port should be 8080.");
    cr_assert_str_eq(server->path, "/tmp", "The server path should be '/tmp'.");
    cr_assert_null(server->clients, "The client list should be empty.");

    destroy_server(server);
}

Test(init_server, invalid_initialization)
{
    cr_assert_null(init_server(0, "/tmp"), "Server initialization should fail with invalid port.");
    cr_assert_null(init_server(8080, "/nonexistent_path"), "Server initialization should fail with invalid path.");
    cr_assert_null(init_server(8080, NULL), "Server initialization should fail with NULL path.");
}

Test(destroy_server, null_server)
{
    destroy_server(NULL);
}

Test(destroy_server, valid_server)
{
    server_t *server = init_server(8080, "/tmp");

    cr_assert_not_null(server, "The server should be initialized for destruction test.");
    destroy_server(server);
    cr_assert(1, "Server should be destroyed without crashing.");
}
