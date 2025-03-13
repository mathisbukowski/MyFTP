/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** DeleCommand
*/

#ifndef DELECOMMAND_HPP_
#define DELECOMMAND_HPP_

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class DeleCommand : public ACommand {
        public:
            DeleCommand();
            ~DeleCommand() = default;
            void execute(std::string args, Client &client) override;
        protected:
        private:
    };
}

#endif /* !DELECOMMAND_HPP_ */
