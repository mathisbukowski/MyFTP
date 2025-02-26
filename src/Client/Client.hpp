/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../../include/ftp.hpp"
#include <cstring>

namespace ftp {
    class Client {
    public:
        Client(int clientSocket);
        ~Client();
        int getSocket() const;
        void setSocket(const int socket);
        int getLoggedIn() const;
        void setLoggedIn(const int logged_in);
        int getDataSocket() const;
        void setDataSocket(const int data_socket);
        int getPassiveMode() const;
        void setPassiveMode(const int passive_mode);
        sockaddr_in getDataAddr() const;
        void setDataAddr(const sockaddr_in& data_addr);
        void setUsername(const std::string& username);
        std::string getUsername() const;
        void setCwd(const std::string& cwd);
        std::string getCwd() const;

        protected:
            int _socket;
            int _logged_in;
            int _data_socket;
            int _passive_mode;
            sockaddr_in _data_addr;
            std::string _username;
            std::string _cwd;
        private:
    };
};

#endif /* !CLIENT_HPP_ */
