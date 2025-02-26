/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "TestCommand.hpp"

ftp::TestCommand::TestCommand()
{
}

void ftp::TestCommand::execute(std::string args, ftp::Client &client)
{
    (void)args;
    log_command("PWD", "", client.getSocket());
    dprintf(client.getSocket(), "257 \"%s\"\n", "TestCommand");
}