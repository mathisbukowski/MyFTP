/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#ifndef PASVCOMMAND_HPP
#define PASVCOMMAND_HPP

#include "../ACommand.hpp"
#include "../../Client/Client.hpp"

namespace ftp {
    class PasvCommand : public ACommand {
    public:
        PasvCommand();
        ~PasvCommand() = default;
        void execute(std::string args, Client &client) override;
        void sendPassiveModeResponse(Client& client, sockaddr_in& data_address);
        sockaddr_in getDataAddress(Client& client, int data_socket);
        int createDataSocket(Client& client);
    };
}



#endif //PASVCOMMAND_HPP
