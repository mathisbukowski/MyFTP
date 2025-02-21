/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#ifndef FTP_H
    #define FTP_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #define LOCALHOST "127.0.0.1"
    #define LENGTH_COMMANDS 20

typedef struct client_s {
    int socket;
    int logged_in;
    int data_socket;
    int passive_mode;
    struct sockaddr_in data_addr;
    char username[256];
    char cwd[1024];
    struct client_s *next;
} client_t;

typedef struct command_s {
    char *name;
    void (*func)(client_t *client, char *args);
} command_t;

typedef struct server_s {
    int port;
    char *path;
    int socket;
    client_t *clients;
} server_t;

extern const command_t commands[LENGTH_COMMANDS];

// server structure
server_t *init_server(int port, char *path);
void destroy_server(server_t *server);
int ftp_server(server_t *server);
int checking_server_error(server_t *server, struct sockaddr_in *sin,
    char *address);
int check_port(int port);
int check_path(char *path);
//client
void add_client(server_t *server, int client_socket);
void add_new_client(server_t *server, client_t *new_client);
void remove_client(server_t *server, int client_socket);
void delete_all_clients(server_t *server);
client_t *find_client(server_t *server, int client_socket);
client_t *find_last(server_t *server);
void remove_or_update_list(server_t *server, client_t *curr, client_t *prev);

//utils
char **str_to_word_array(char *str, char const *delimiters);
int word_length(char *str, int i, const char *delimiters);
int count_words_in_array(char *tab, const char *delimiters);
int iscustomalphanum(char letter, char const *delimiters);

//commands
void handle_commands(client_t *client, char *command);
void user_command(client_t *client, char *args);
void password_command(client_t *client, char *args);
void cwd_command(client_t *client, char *args);
void quit_command(client_t *client, char *args);
void port_command(client_t *client, char *args);
void cdup_command(client_t *client, char *args);
void test_command(client_t *client, char *args);

#endif //FTP_H
