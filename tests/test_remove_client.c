/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_remove_client
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "ftp.h"

static server_t server;
static client_t *client1, *client2, *client3;

void setup_rm(void) {
    client1 = malloc(sizeof(client_t));
    client2 = malloc(sizeof(client_t));
    client3 = malloc(sizeof(client_t));

    client1->socket = 10;
    client2->socket = 20;
    client3->socket = 30;

    client1->next = client2;
    client2->next = client3;
    client3->next = client1;  
    server.clients = client1;
}

void teardown_rm(void) {
    if (server.clients) {
        client_t *curr = server.clients;
        client_t *next;
        do {
            next = curr->next;
            free(curr);
            curr = next;
        } while (curr != server.clients);
    }
    server.clients = NULL;
}

Test(remove_client, remove_existing_client, .init = setup_rm, .fini = teardown_rm) {
    remove_client(&server, 20);
    cr_assert_not_null(server.clients);
    cr_assert_eq(server.clients->next->socket, 30);
    cr_assert_eq(server.clients->next->next, server.clients);
}

Test(remove_client, remove_first_client, .init = setup_rm, .fini = teardown_rm) {
    remove_client(&server, 10);
    cr_assert_not_null(server.clients);
    cr_assert_eq(server.clients->socket, 20);
    cr_assert_eq(server.clients->next->next, server.clients);
}

Test(remove_client, remove_last_client, .init = setup_rm, .fini = teardown_rm) {
    remove_client(&server, 30);
    cr_assert_not_null(server.clients);

    cr_assert_eq(server.clients->next->next, server.clients);
}

Test(remove_client, remove_single_client) {
    server_t single_server = {0};
    client_t *single_client = malloc(sizeof(client_t));
    
    single_client->socket = 10;
    single_client->next = single_client;
    single_server.clients = single_client;

    remove_client(&single_server, 10);
    cr_assert_null(single_server.clients);
}

Test(remove_client, remove_non_existing_client, .init = setup_rm, .fini = teardown_rm) {
    remove_client(&server, 99);
    cr_assert_not_null(server.clients);
    cr_assert_eq(server.clients->socket, 10);
    cr_assert_eq(server.clients->next->next->next, server.clients);
}

Test(remove_client, remove_from_empty_list) {
    server_t empty_server = { .clients = NULL };
    remove_client(&empty_server, 10);
    cr_assert_null(empty_server.clients);
}

Test(delete_all_clients, delete_all, .init = setup_rm, .fini = teardown_rm) {
    delete_all_clients(&server);
    cr_assert_null(server.clients);
}

Test(delete_all_clients, delete_empty_list) {
    server_t empty_server = { .clients = NULL };
    delete_all_clients(&empty_server);
    cr_assert_null(empty_server.clients);
}