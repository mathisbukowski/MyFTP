/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#ifndef PASVCOMMAND_HPP
#define PASVCOMMAND_HPP

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class PasvCommand : public ACommand {
    public:
        PasvCommand();
        ~PasvCommand() = default;
        void execute(std::string args, Client &client) override;
    };
}



#endif //PASVCOMMAND_HPP
