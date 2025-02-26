/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "../../include/ftp.hpp"
#include "../Server/Server.hpp"
#include "../Command/Commands/PwdCommand.hpp"
#include "../Command/Commands/CwdCommand.hpp"
#include "../Command/Commands/CdupCommand.hpp"
#include "../Command/Commands/UserCommand.hpp"
#include "../Command/Commands/PasswordCommand.hpp"
#include "../Command/Commands/QuitCommand.hpp"
#include "../Command/Commands/HelpCommand.hpp"
#include "../Command/Commands/NoopCommand.hpp"
#include <map>
#include <memory>
#include <functional>

namespace ftp {
    class CommandHandler {
    public:
        CommandHandler(Server &server);
        ~CommandHandler();
        std::unique_ptr<ftp::ICommand> handleCommand(std::string command, Client &client);
    protected:
    private:
        Server &_server;
        std::map<std::string, std::function<std::unique_ptr<ICommand>()>> _commands;
    };
};



#endif //COMMANDHANDLER_HPP
