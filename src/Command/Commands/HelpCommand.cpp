/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#include "HelpCommand.hpp"

ftp::HelpCommand::HelpCommand()
{
}

void ftp::HelpCommand::execute(std::string args, Client &client)
{
    (void)args;
    dprintf(client.getSocket(), "214 The following commands are recognized.\r\n");
    dprintf(client.getSocket(), "USER PASS CWD CDUP QUIT PWD HELP NOOP\r\n");
    dprintf(client.getSocket(), "USER <SP> Username <CRLF> \r\n");
    dprintf(client.getSocket(), "PASS <SP> Password <CRLF> \r\n");
    dprintf(client.getSocket(), "CWD  <SP> pathname <CRLF> \r\n");
    dprintf(client.getSocket(), "CDUP <CRLF> \r\n");
    dprintf(client.getSocket(), "QUIT <CRLF> \r\n");
    dprintf(client.getSocket(), "PWD  <CRLF> \r\n");
    dprintf(client.getSocket(), "HELP <CRLF> \r\n");
    dprintf(client.getSocket(), "NOOP <CRLF> \r\n");
    dprintf(client.getSocket(), "SP = Space character <CRLF> = Carriage return and Line feed\r\n");
    dprintf(client.getSocket(), "214 Help OK.\r\n");
}
