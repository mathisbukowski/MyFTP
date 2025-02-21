/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_find_client
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "ftp.h"
#include <stdlib.h>

static server_t server;
static client_t client1, client2, client3;

void setup_find(void) {
    client1.socket = 10;
    client2.socket = 20;
    client3.socket = 30;

    client1.next = &client2;
    client2.next = &client3;
    client3.next = NULL;

    server.clients = &client1;
}

void teardown_find(void) {
    server.clients = NULL;
}

Test(find_client, existing_client, .init = setup_find, .fini = teardown_find) {
    client_t *found = find_client(&server, 20);
    cr_assert_not_null(found, "Client with socket 20 must be find.");
    cr_assert_eq(found->socket, 20, "None socket.");
}

Test(find_client, non_existing_client, .init = setup_find, .fini = teardown_find) {
    client_t *found = find_client(&server, 99);
    cr_assert_null(found, "none client find with this socket.");
}

Test(find_client, empty_list) {
    server_t empty_server = { .clients = NULL };
    client_t *found = find_client(&empty_server, 10);
    cr_assert_null(found, "NULL list.");
}
