/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef CWDCOMMAND_HPP
#define CWDCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class CwdCommand : public ACommand {
    public:
        CwdCommand();
        ~CwdCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:

    };
}


#endif //CWDCOMMAND_HPP
