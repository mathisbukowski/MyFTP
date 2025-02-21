/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** test_remove_client
*/

#include <criterion/criterion.h>
#include "ftp.h"
#include "test_utils.h"

Test(find_last, null_server)
{
    cr_assert_null(find_last(NULL));
}

Test(find_last, empty_server)
{
    server_t server = {0, NULL, 0, NULL};
    cr_assert_null(find_last(&server));
}

Test(find_last, single_client)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client = malloc(sizeof(client_t));

    client->socket = 42;
    client->next = client;
    client->data_socket = -1;
    client->logged_in = 0;
    server.clients = client;

    client_t *result = find_last(&server);
    cr_assert_eq(result, client);

    free(client);
}

Test(find_last, multiple_clients)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client1 = malloc(sizeof(client_t));
    client_t *client2 = malloc(sizeof(client_t));
    client_t *client3 = malloc(sizeof(client_t));

    client1->socket = 1;
    client1->data_socket = -1;
    client1->logged_in = 0;
    client2->socket = 2;
    client2->data_socket = -1;
    client2->logged_in = 0;
    client3->socket = 3;
    client3->data_socket = -1;
    client3->logged_in = 0;

    client1->next = client2;
    client2->next = client3;
    client3->next = client1;

    server.clients = client1;

    client_t *result = find_last(&server);
    cr_assert_eq(result, client3);

    free(client1);
    free(client2);
    free(client3);
}

Test(remove_or_update_list, null_server)
{
    client_t client = {42, 0, -1, 0, {0}, "", "", NULL};
    remove_or_update_list(NULL, &client, NULL);
}

Test(remove_or_update_list, null_client)
{
    server_t server = {0, NULL, 0, NULL};
    remove_or_update_list(&server, NULL, NULL);
}

Test(remove_or_update_list, single_client)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client = malloc(sizeof(client_t));

    client->socket = 42;
    client->next = client;
    client->data_socket = -1;
    client->logged_in = 0;
    server.clients = client;

    remove_or_update_list(&server, client, NULL);
    cr_assert_null(server.clients);
}

Test(remove_or_update_list, remove_first_multiple_clients)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client1 = malloc(sizeof(client_t));
    client_t *client2 = malloc(sizeof(client_t));

    client1->socket = 1;
    client1->data_socket = -1;
    client1->logged_in = 0;
    client2->socket = 2;
    client2->data_socket = -1;
    client2->logged_in = 0;

    client1->next = client2;
    client2->next = client1;
    server.clients = client1;

    remove_or_update_list(&server, client1, NULL);
    cr_assert_eq(server.clients, client2);
    cr_assert_eq(server.clients->next, client2);

    free(client2);
}

Test(remove_or_update_list, remove_middle_client)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client1 = malloc(sizeof(client_t));
    client_t *client2 = malloc(sizeof(client_t));
    client_t *client3 = malloc(sizeof(client_t));

    client1->socket = 1;
    client1->data_socket = -1;
    client1->logged_in = 0;
    client2->socket = 2;
    client2->data_socket = -1;
    client2->logged_in = 0;
    client3->socket = 3;
    client3->data_socket = -1;
    client3->logged_in = 0;

    client1->next = client2;
    client2->next = client3;
    client3->next = client1;
    server.clients = client1;

    remove_or_update_list(&server, client2, client1);
    cr_assert_eq(client1->next, client3);

    free(client1);
    free(client3);
}

Test(remove_client, null_server)
{
    remove_client(NULL, 42);
}

Test(remove_client, empty_server)
{
    server_t server = {0, NULL, 0, NULL};
    remove_client(&server, 42);
}

Test(remove_client, client_not_found)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client = malloc(sizeof(client_t));

    client->socket = 42;
    client->data_socket = -1;
    client->logged_in = 0;
    client->next = client;
    server.clients = client;

    remove_client(&server, 43);
    cr_assert_eq(server.clients, client);

    free(client);
}

Test(remove_client, remove_existing_client)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client1 = malloc(sizeof(client_t));
    client_t *client2 = malloc(sizeof(client_t));

    client1->socket = 1;
    client1->data_socket = -1;
    client1->logged_in = 0;
    client2->socket = 2;
    client2->data_socket = -1;
    client2->logged_in = 0;

    client1->next = client2;
    client2->next = client1;
    server.clients = client1;

    remove_client(&server, 2);
    cr_assert_eq(server.clients, client1);
    cr_assert_eq(server.clients->next, client1);

    free(client1);
}

Test(delete_all_clients, null_server)
{
    delete_all_clients(NULL);
}

Test(delete_all_clients, empty_server)
{
    server_t server = {0, NULL, 0, NULL};
    delete_all_clients(&server);
    cr_assert_null(server.clients);
}

Test(delete_all_clients, delete_multiple_clients)
{
    server_t server = {0, NULL, 0, NULL};
    client_t *client1 = malloc(sizeof(client_t));
    client_t *client2 = malloc(sizeof(client_t));
    client_t *client3 = malloc(sizeof(client_t));

    client1->socket = 1;
    client1->data_socket = -1;
    client1->logged_in = 0;
    client2->socket = 2;
    client2->data_socket = -1;
    client2->logged_in = 0;
    client3->socket = 3;
    client3->data_socket = -1;
    client3->logged_in = 0;

    client1->next = client2;
    client2->next = client3;
    client3->next = client1;
    server.clients = client1;

    delete_all_clients(&server);
    cr_assert_null(server.clients);
}