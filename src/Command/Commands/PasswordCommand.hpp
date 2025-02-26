/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef PASSWORDCOMMAND_HPP
#define PASSWORDCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class PasswordCommand : public ACommand {
    public:
        PasswordCommand();
        ~PasswordCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:

    };
}


#endif //PASSWORDCOMMAND_HPP
