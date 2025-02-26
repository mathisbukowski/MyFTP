/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef HELPCOMMAND_HPP
#define HELPCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class HelpCommand : public ACommand {
    public:
        HelpCommand();
        ~HelpCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:

    };
}


#endif //HELPCOMMAND_HPP
