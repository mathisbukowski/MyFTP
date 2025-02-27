/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef RETRCOMMAND_HPP
#define RETRCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class RetrCommand
        : public ACommand {
        public:
            RetrCommand();
            ~RetrCommand() = default;
            void execute(std::string args, ftp::Client &client) override;
        protected:
        private:
    };
}



#endif //RETRCOMMAND_HPP
