/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include "../../include/ftp.hpp"
#include "../Client/Client.hpp"


namespace ftp {
    class ACommand : public ICommand {
    public:
        virtual ~ACommand() = default;
        virtual void execute(std::string args, Client &client) = 0;
        int acceptDataConnection(Client &client);
    protected:
        std::string _command;
        std::string _arg;
    };
};
#endif //ACOMMAND_HPP
