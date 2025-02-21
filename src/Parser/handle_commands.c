/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "ftp.h"

command_t const commands[LENGTH_COMMANDS] = {
    {"USER", &user_command},
    {"PASS", &password_command},
    {"CWD", &cwd_command},
    {"CDUP", &cdup_command},
    {"QUIT", &quit_command},
    {"PORT", &port_command},
    {"TEST", &test_command},
    {"PWD", &pwd_command},
    {NULL, NULL}
};

void handle_commands(client_t *client, char *command)
{
    char **commandArray = str_to_word_array(command, " ");
    int i = 0;
    char *arg = commandArray[1] ? commandArray[1] : NULL;

    while (commands[i].name) {
        if (strcmp(commands[i].name, commandArray[0]) == 0) {
            commands[i].func(client, arg);
            break;
        }
        i++;
    }
    if (!commands[i].name)
        dprintf(client->socket, "500 Unknown command.\n");
    for (int j = 0; commandArray[j]; j++)
        free(commandArray[j]);
    free(commandArray);
}
