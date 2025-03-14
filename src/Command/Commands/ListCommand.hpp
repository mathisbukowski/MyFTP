/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#ifndef LISTCOMMAND_HPP
#define LISTCOMMAND_HPP

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class ListCommand
        : public ACommand {
    public:
        ListCommand();
        void execute(std::string args, Client &client) override;
    };
}

#endif //LISTCOMMAND_HPP
