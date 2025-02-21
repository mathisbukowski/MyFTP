/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#include "ftp.h"

static void handle_client_connection(server_t *server, struct pollfd *fds,
    int *nfds)
{
    int client_socket = accept(server->socket, NULL, NULL);

    if (client_socket == -1) {
        fprintf(stderr, "Error: accept\n");
        return;
    }
    printf("New client connected\n");
    add_client(server, client_socket);
    fds[*nfds].fd = client_socket;
    fds[*nfds].events = POLLIN;
    (*nfds)++;
}

static void handle_client_data(server_t *server, struct pollfd *fds,
    int *nfds, int index)
{
    char buff_read[1024] = {0};
    ssize_t bytes_read = read(fds[index].fd, buff_read, sizeof(buff_read) - 1);

    if (bytes_read <= 0) {
        if (bytes_read == 0)
            printf("Client disconnected\n");
        else
            fprintf(stderr, "Error: read\n");
        close(fds[index].fd);
        remove_client(server, fds[index].fd);
        (*nfds)--;
        fds[index] = fds[(*nfds)];
        return;
    }
    buff_read[bytes_read] = '\0';
    handle_commands(find_client(server, fds[index].fd), buff_read);
    printf("Received: %s\n", buff_read);
}

void handle_input(int *nfds, struct pollfd *fds, server_t *server)
{
    for (int i = 0; i < *nfds; i++) {
        if (!(fds[i].revents & POLLIN))
            continue;
        if (fds[i].fd == server->socket)
            handle_client_connection(server, fds, nfds);
        else
            handle_client_data(server, fds, nfds, i);
    }
}

void client_management(server_t *server)
{
    struct pollfd fds[1024];
    int nfds = 1;
    int ret = 0;

    fds[0].fd = server->socket;
    fds[0].events = POLLIN;
    while (1) {
        ret = poll(fds, nfds, -1);
        if (ret == -1) {
            fprintf(stderr, "Error: poll\n");
            break;
        }
        handle_input(&nfds, fds, server);
    }
}

int checking_server_error(server_t *server, struct sockaddr_in *sin)
{
    if (server->socket == -1) {
        fprintf(stderr, "Error: socket\n");
        return 84;
    }
    if (inet_pton(AF_INET, LOCALHOST, &sin->sin_addr) != 1) {
        fprintf(stderr, "Error: inet_pton\n");
        return 84;
    }
    return 0;
}

int ftp_server(server_t *server)
{
    struct sockaddr_in sin;

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (checking_server_error(server, &sin) == 84)
        return 84;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(server->port);
    if (bind(server->socket, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
        fprintf(stderr, "Error: bind\n");
        return 84;
    }
    if (listen(server->socket, 42) == -1) {
        fprintf(stderr, "Error: listen\n");
        return 84;
    }
    printf("Server started on port %d\n", server->port);
    client_management(server);
    return 0;
}
