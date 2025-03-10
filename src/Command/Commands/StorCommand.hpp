/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#ifndef STORCOMMAND_HPP
#define STORCOMMAND_HPP

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class StorCommand : public ACommand {
    public:
        StorCommand();
        ~StorCommand() = default;
        void execute(std::string args, Client &client) override;
    };
}

#endif //STORCOMMAND_HPP
