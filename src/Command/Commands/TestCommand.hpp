/*
** EPITECH PROJECT, 2025
** MyFTP
** File description:
** 02
*/

#ifndef TESTCOMMAND_HPP
#define TESTCOMMAND_HPP

#include "../../../include/ftp.hpp"
#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class TestCommand : public ACommand {
    public:
        TestCommand();
        ~TestCommand() = default;
        void execute(std::string args, Client &client) override;
    protected:
    private:

    };
}



#endif //TESTCOMMAND_HPP
