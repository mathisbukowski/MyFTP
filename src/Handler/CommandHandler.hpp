/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "../../include/ftp.hpp"
#include "../Command/Commands/PwdCommand.hpp"
#include "../Command/Commands/TestCommand.hpp"
#include <map>
#include <memory>
#include <functional>

namespace ftp {
    class CommandHandler {
    public:
        CommandHandler();
        ~CommandHandler();
        std::unique_ptr<ftp::ICommand> handleCommand(std::string command, Client &client);
    protected:
    private:
        std::map<std::string, std::function<std::unique_ptr<ICommand>()>> _commands;
    };
};



#endif //COMMANDHANDLER_HPP
