/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** RetrCommand
*/

#ifndef RETRCOMMAND_HPP_
#define RETRCOMMAND_HPP_

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class RetrCommand
        : public ACommand {
        public:
            RetrCommand();
            ~RetrCommand() = default;
            void execute(std::string args, Client &client) override;
    };
}


#endif /* !RETRCOMMAND_HPP_ */
