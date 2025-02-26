/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "PwdCommand.hpp"

ftp::PwdCommand::PwdCommand()
{
}

void ftp::PwdCommand::execute(std::string args, ftp::Client &client)
{
    (void)args;
    log_command("PWD", "", client.getSocket());
    std::string pwd = client.getCwd();
    dprintf(client.getSocket(), "257 \"%s\"\n", pwd.c_str());
}