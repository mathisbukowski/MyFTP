/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class UserCommand : public ACommand {
    public:
        UserCommand();
        ~UserCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:

    };
}


#endif //USERCOMMAND_HPP
