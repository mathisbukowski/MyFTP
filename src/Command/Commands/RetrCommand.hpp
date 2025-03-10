/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#ifndef RETRCOMMAND_HPP
#define RETRCOMMAND_HPP
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"


namespace ftp {
    class RetrCommand : public ACommand {
    public:
        RetrCommand();
        ~RetrCommand() = default;
        void execute(std::string args, Client &client) override;
    };
}



#endif //RETRCOMMAND_HPP
