/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef STORCOMMAND_HPP
#define STORCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class StorCommand : public ACommand {
        public:
            StorCommand();
            ~StorCommand() = default;
            void execute(std::string args, ftp::Client &client) override;
        protected:
        private:
    };
}


#endif //STORCOMMAND_HPP
