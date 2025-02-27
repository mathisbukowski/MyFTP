/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#include "CommandHandler.hpp"


ftp::CommandHandler::CommandHandler(Server &server) : _server(server)
{
    _commands = {
        {"PWD", []() { return std::make_unique<PwdCommand>(); }},
        {"USER", []() { return std::make_unique<UserCommand>(); }},
        {"PASS", []() { return std::make_unique<PasswordCommand>(); }},
        {"QUIT", [&server]() { return std::make_unique<QuitCommand>(server); }},
        {"CWD", []() {return std::make_unique<CwdCommand>(); }},
        {"CDUP", []() {return std::make_unique<CdupCommand>(); }},
        {"HELP", []() {return std::make_unique<HelpCommand>(); }},
        {"NOOP", []() {return std::make_unique<NoopCommand>(); }},
        {"PORT", []() {return std::make_unique<PortCommand>(); }},
        {"PASV", []() {return std::make_unique<PasvCommand>(); }},
        {"RETR", []() {return std::make_unique<RetrCommand>(); }},
        {"STOR", []() {return std::make_unique<StorCommand>(); }},
        {"LIST", []() {return std::make_unique<ListCommand>(); }},
    };
}

ftp::CommandHandler::~CommandHandler()
{
}

std::unique_ptr<ftp::ICommand> ftp::CommandHandler::handleCommand(std::string command, Client &client)
{
    for (auto &cmd : _commands) {
        if (cmd.first == command) {
            return cmd.second();
        }
    }
    dprintf(client.getSocket(), "500 Unknown command\n");
    return nullptr;
}