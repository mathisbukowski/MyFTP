/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#ifndef PORTCOMMAND_HPP
#define PORTCOMMAND_HPP

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class PortCommand : public ACommand
    {
    public:
        PortCommand();
        ~PortCommand() = default;
        void execute(std::string args, Client &client);
    };
}



#endif //PORTCOMMAND_HPP
