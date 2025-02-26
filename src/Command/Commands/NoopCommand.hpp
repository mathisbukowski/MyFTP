/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef NOOPCOMMAND_HPP
#define NOOPCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class NoopCommand : public ACommand
    {
    public:
        NoopCommand();
        ~NoopCommand() = default;
        void execute(std::string args, Client &client);
    protected:
    private:

    };
}



#endif //NOOPCOMMAND_HPP
