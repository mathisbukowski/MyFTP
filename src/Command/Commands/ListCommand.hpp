/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef LISTCOMMAND_HPP
#define LISTCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class ListCommand : public ACommand {
        public:
            ListCommand();
            ~ListCommand() = default;
            void execute(std::string args, ftp::Client &client) override;
        protected:
        private:
    };
}


#endif //LISTCOMMAND_HPP
