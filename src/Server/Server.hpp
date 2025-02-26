/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_
#include "../../include/ftp.hpp"
#include "../Client/Client.hpp"
#include "../Handler/CommandHandler.hpp"
#include <algorithm>
#define MAX_CLIENTS 20

namespace ftp {
    class Server {
        class ServerError : public std::exception {
            public:
                ServerError(std::string const &message) : _message(message) {};
                const char *what() const noexcept override { return _message.c_str(); };
            private:
                std::string _message;
        };
        public:
            Server(int port, std::string path);
            ~Server();
            int process();
            void run();
            void clientManagement();
            void stop();
            void setPort(int port);
            void setRootPath(std::string path);
            int getPort() const;
            std::string getRootPath() const;
            void addNewClient(int client_socket);
            Client *getClient(int client_socket);
            void removeClient(int client_socket);
            int checkPort(int port);
            int checkPath(std::string path);
            void handleClientDisconnection(pollfd *fds, int *nfds, int *i);
            void handleClientInput(pollfd *fds, int *nfds);
            void setServerAddr(sockaddr_in serverAddr);
            sockaddr_in getServerAddr() const;
            std::string getCommand(char *buffer);
            std::string getArgs(char *buffer);
            void cleanBuffer(char *buffer);

        protected:
            std::vector<Client> _clients;
            int _port;
            std::string _rootPath;
            int _socketServer;
            pollfd _fds[10];
            sockaddr_in _serverAddr;
        private:
    };
};

#endif /* !SERVER_HPP_ */
