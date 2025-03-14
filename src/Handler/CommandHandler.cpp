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
        {"pwd", []() { return std::make_unique<PwdCommand>(); }},
        {"user", []() { return std::make_unique<UserCommand>(); }},
        {"pass", []() { return std::make_unique<PasswordCommand>(); }},
        {"quit", [&server]() { return std::make_unique<QuitCommand>(server); }},
        {"cwd", []() {return std::make_unique<CwdCommand>(); }},
        {"cdup", []() {return std::make_unique<CdupCommand>(); }},
        {"help", []() {return std::make_unique<HelpCommand>(); }},
        {"noop", []() {return std::make_unique<NoopCommand>(); }},
        {"pasv", []() { return std::make_unique<PasvCommand>(); }},
        {"port", []() {return std::make_unique<PortCommand>(); }},
        {"stor", []() { return std::make_unique<StorCommand>(); }},
        {"dele", []() { return std::make_unique<DeleCommand>(); }},
        {"retr", []() { return std::make_unique<RetrCommand>(); }},
        {"list", []() { return std::make_unique<ListCommand>(); }}
    };
}

ftp::CommandHandler::~CommandHandler()
{
}

std::unique_ptr<ftp::ICommand> ftp::CommandHandler::handleCommand(std::string command)
{
    for (auto &cmd : _commands) {
        if (cmd.first == command) {
            return cmd.second();
        }
    }
    return nullptr;
}