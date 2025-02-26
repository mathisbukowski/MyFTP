/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 02
*/

#ifndef CDUPCOMMAND_HPP
#define CDUPCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class CdupCommand : public ACommand {
    public:
        CdupCommand();
        ~CdupCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:
    };
};

#endif //CDUPCOMMAND_HPP
