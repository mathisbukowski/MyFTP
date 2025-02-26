/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#ifndef PWDCOMMAND_HPP
#define PWDCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class PwdCommand : public ftp::ACommand {
    public:
        PwdCommand();
        ~PwdCommand() = default;
        void execute(std::string args, ftp::Client &client) override;
    protected:
    private:

    };
}



#endif //PWDCOMMAND_HPP
