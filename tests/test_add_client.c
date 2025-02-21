/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_add_client
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "ftp.h"
#include "test_utils.h"

static server_t server;

void setup_add(void)
{
    server.clients = NULL;
}

void teardown_add(void)
{
    if (!server.clients)
        return;

    client_t *curr = server.clients;
    client_t *next = NULL;

    do {
        next = curr->next;
        free(curr);
        curr = next;
    } while (curr != server.clients);

    server.clients = NULL;
}

Test(add_new_client, add_to_existing_list, .init = setup_add, .fini = teardown_add)
{
    client_t *client1 = malloc(sizeof(client_t));
    client_t *client2 = malloc(sizeof(client_t));

    cr_assert_not_null(client1, "Allocation of client1 failed.");
    cr_assert_not_null(client2, "Allocation of client2 failed.");

    client1->socket = 10;
    client1->next = client1;
    server.clients = client1;

    client2->socket = 20;
    add_new_client(&server, client2);

    cr_assert_eq(client1->next->socket, 20, "Client2 should follow Client1.");
    cr_assert_eq(client2->next, client1, "Client2 should point to the first client.");
}

Test(add_new_client, null_server_or_client, .init = setup_add, .fini = teardown_add)
{
    client_t *new_client = malloc(sizeof(client_t));
    cr_assert_not_null(new_client, "Allocation of new_client failed.");
    new_client->socket = 30;

    add_new_client(NULL, new_client);
    cr_assert_neq(new_client->next, new_client, "The client should not be modified if the server is NULL.");

    add_new_client(&server, NULL);
    cr_assert_null(server.clients, "The list should not change if the client is NULL.");

    free(new_client);
}

Test(add_client, add_first_client, .init = setup_add, .fini = teardown_add)
{
    add_client(&server, 10);

    cr_assert_not_null(server.clients, "The client list should not be empty after adding a client.");
    cr_assert_eq(server.clients->socket, 10, "The first client should have socket 10.");
    cr_assert_eq(server.clients->next, server.clients, "The first client should point to itself.");
}

Test(add_client, add_multiple_clients, .init = setup_add, .fini = teardown_add)
{
    add_client(&server, 10);
    add_client(&server, 20);
    add_client(&server, 30);

    client_t *first = server.clients;
    client_t *second = first->next;
    client_t *third = second->next;

    cr_assert_eq(first->socket, 10, "The first client should have socket 10.");
    cr_assert_eq(second->socket, 20, "The second client should have socket 20.");
    cr_assert_eq(third->socket, 30, "The third client should have socket 30.");
    cr_assert_eq(third->next, first, "The last client should point to the first one.");
}

Test(add_client, null_server, .fini = teardown_add)
{
    add_client(NULL, 10);
    cr_assert_null(server.clients, "Nothing should be added if the server is NULL.");
}

Test(add_client, malloc_failure, .init = setup_add, .fini = teardown_add)
{
    server_t *new_serv = malloc(sizeof(server_t));
    new_serv->clients = NULL;
    int initial_socket = 42;
    should_malloc_fail = 1;
    add_client(new_serv, initial_socket);
    cr_assert_null(new_serv->clients);
    should_malloc_fail = 0;
    free(new_serv);
}
