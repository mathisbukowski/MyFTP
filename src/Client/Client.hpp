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
#include <filesystem>
#include <map>

namespace ftp {
    class Client {
    public:
        Client(int clientSocket);
        ~Client();
        int getSocket() const { return _socket; }
        bool isLoggedIn() const { return _logged_in; }
        int getDataSocket() const { return _data_socket; }
        bool isPassiveMode() const { return _passive_mode; }
        bool isActiveMode() const { return _active_mode; }
        sockaddr_in getDataAddr() const { return _data_addr; }
        const std::string &getUsername() const { return _username; }
        const std::filesystem::path &getCwd() const { return _cwd; }
        const std::filesystem::path &getRootPath() const { return _root_path; }
        const std::filesystem::path &getRootDir() const { return _rootDir; }

        void setSocket(int socket) { _socket = socket; }
        void setLoggedIn(bool logged_in) { _logged_in = logged_in; }
        void setDataSocket(int data_socket) { _data_socket = data_socket; }
        void setPassiveMode(bool passive_mode) { _passive_mode = passive_mode; }
        void setDataAddr(const sockaddr_in &data_addr) { _data_addr = data_addr; }
        void setUsername(const std::string &username) { _username = username; }
        void setCwd(const std::filesystem::path &cwd) { _cwd = cwd; }
        void setRootPath(const std::filesystem::path &root_path) { _root_path = root_path; }
        void setActiveMode(bool active_mode) { _active_mode = active_mode; }
        void setRootDir(const std::string &rootDir) { _rootDir = rootDir; }

        void resetDataMode();
        void sendCustomResponse(int code, const std::string& custom_message);
        void sendCommandResponse(int code);
        void sendPasvResponse();

        protected:
            int _socket;
            bool _logged_in;
            int _data_socket;
            bool _passive_mode;
            bool _active_mode;
            sockaddr_in _data_addr;
            std::string _username;
            std::filesystem::path _cwd;
            std::map<int, std::string> _commandResponses;
            std::filesystem::path _root_path;
            std::filesystem::path _rootDir;
    };
};

#endif /* !CLIENT_HPP_ */
