/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef PASVCOMMAND_HPP
#define PASVCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class PasvCommand
        : public ACommand {
        public:
            PasvCommand();
            ~PasvCommand() = default;
            void execute(std::string args, ftp::Client &client) override;
        protected:
        private:
    };
}



#endif //PASVCOMMAND_HPP
