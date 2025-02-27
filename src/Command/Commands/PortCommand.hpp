/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef PORTCOMMAND_HPP
#define PORTCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"
#include <vector>
#include <sstream>


namespace ftp {
    class PortCommand
        : public ACommand {
        public:
            PortCommand();
            ~PortCommand() = default;
            void execute(std::string args, ftp::Client &client) override;
            sockaddr_in createAddr(const std::string &ip, int port);
            std::vector<std::string> split(const std::string &s, char delimiter);
        protected:
        private:
    };
}


#endif //PORTCOMMAND_HPP
