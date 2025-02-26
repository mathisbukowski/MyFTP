/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"
#include "../../Server/Server.hpp"

namespace ftp {
    class QuitCommand : public ACommand {
    public:
        QuitCommand(Server &server);
        ~QuitCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:
        Server &_server;
    };
}



#endif //QUITCOMMAND_HPP
