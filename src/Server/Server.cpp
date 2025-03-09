/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** Server
*/

#include "Server.hpp"

ftp::Server::Server(int port, std::string path)
{
    _port = port;
    _rootPath = get_current_dir_name();
    _rootPath += "/" + path;
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    _serverAddr = {};
    _fds.reserve(MAX_CLIENTS);
}


int ftp::Server::getPort() const
{
    return _port;
}

std::string ftp::Server::getRootPath() const
{
    return _rootPath;
}

void ftp::Server::setPort(int port)
{
    _port = port;
}

void ftp::Server::setRootPath(std::string path)
{
    _rootPath = path;
}

void ftp::Server::setServerAddr(sockaddr_in serverAddr)
{
    _serverAddr = serverAddr;
}

sockaddr_in ftp::Server::getServerAddr() const
{
    return _serverAddr;
}

void ftp::Server::addNewClient(int client_socket, sockaddr_in clientAddr)
{
    _clients.emplace_back(client_socket);
    for (auto &client : _clients)
        if (client.getSocket() == client_socket) {
            client.setCwd(_rootPath);
            client.setDataAddr(clientAddr);
            break;
        }
}

ftp::Client *ftp::Server::getClient(int client_socket)
{
    for (auto &client : _clients)
        if (client.getSocket() == client_socket)
            return &client;
    return nullptr;
}

int ftp::Server::checkPath(std::string path)
{
    if (access(path.c_str(), F_OK) == -1)
        return 84;
    return 0;
}

int ftp::Server::checkPort(int port)
{
    if (port <= 0 || port > 65535)
        return 84;
    return 0;
}

void ftp::Server::run()
{
    if (_socketServer == -1)
        throw ServerError("Error: Invalid socket.");
    if (checkPath(_rootPath) == 84)
        throw ServerError("Error: Invalid root path.");
    if (checkPort(_port) == 84)
        throw ServerError("Error: Invalid port.");
    if (inet_pton(AF_INET, LOCALHOST, &_serverAddr.sin_addr) != 1)
        throw ServerError("Error: Invalid server address.");
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port);
    if (bind(_socketServer, (sockaddr *)&_serverAddr, sizeof(_serverAddr)) == -1)
        throw ServerError("Error: bind failed");
    if (listen(_socketServer, MAX_CLIENTS) == -1)
        throw ServerError("Error: listen failed");
    std::cout << "Server started on port " << _port << std::endl;
    this->clientManagement();
}

int ftp::Server::process()
{
    try {
        this->run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

void ftp::Server::stop()
{
    close(_socketServer);
}

void ftp::Server::removeClient(int client_socket)
{
    _clients.erase(std::remove_if(_clients.begin(), _clients.end(),
        [&](const Client &client) {
            return client.getSocket() == client_socket;
        }),
    _clients.end());
}

void ftp::Server::clientManagement()
{
    int ret = 0;

    _fds.push_back({_socketServer, POLLIN, 0});
    _nfds = 1;
    while (1) {
        ret = poll(_fds.data(), _nfds, -1);
        if (ret == -1) {
            dprintf(_socketServer, "Error: poll failed\n");
            break;
        }
        if (_fds[0].revents & POLLIN) {
            sockaddr_in clientAddr = {};
            socklen_t clientAddrLen = sizeof(clientAddr);
            const int clientSocket = accept(_socketServer,
                reinterpret_cast<struct sockaddr *>(&clientAddr),
                &clientAddrLen);
            if (clientSocket == -1) {
                std::cerr << "Error: accept failed" << std::endl;
                continue;
            }
            _fds.push_back({ clientSocket, POLLIN, 0 });
            _nfds += 1;
            this->addNewClient(clientSocket, clientAddr);
            dprintf(clientSocket, "220 Service ready for new user.\r\n");
            std::cout << "New client connected : " << clientSocket << std::endl;
        }
        this->handleClientInput();
    }
}

void ftp::Server::handleClientDisconnection(int client_socket, bool isQuitCommand)
{
    std::cout << (isQuitCommand ? "Client sent QUIT command: " : "Client disconnected: ") << client_socket << std::endl;
    close(client_socket);
    this->removeClient(client_socket);
    _fds.erase(std::remove_if(_fds.begin(), _fds.end(),
        [&](const pollfd &pfd) { return pfd.fd == client_socket; }),
        _fds.end());
    _nfds = _fds.size();
}


std::string ftp::Server::getCommand(char* buffer)
{
    std::string command = buffer;
    return command.substr(0, command.find(" "));
}


std::string ftp::Server::getArgs(char *buffer)
{
    std::string command = buffer;
    return command.substr(command.find(" ") + 1);
}

void ftp::Server::handleClientInput()
{
    CommandHandler commandHandler(*this);

    for (size_t i = 0; i < _nfds; i++) {
        if (_fds[i].revents & POLLIN) {
            char buffer[1024] = {};
            ssize_t bytes = read(_fds[i].fd, buffer, sizeof(buffer));
            if (bytes == -1)
                return;
            if (bytes == 0) {
                this->handleClientDisconnection(_fds[i].fd, false);
            } else {
                this->cleanBuffer(buffer);
                std::string command = this->getCommand(buffer);
                std::string args = this->getArgs(buffer);
                std::unique_ptr<ICommand> cmd = commandHandler.handleCommand(command, *this->getClient(_fds[i].fd));
                if (cmd) {
                    cmd->execute(args, *this->getClient(_fds[i].fd));
                }
            }
        }
    }
}

void ftp::Server::cleanBuffer(char *buffer)
{
    if (!buffer)
        return;
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
    }
}

ftp::Server::~Server()
{
    if (_socketServer != -1)
        close(_socketServer);
    _fds.clear();
    _clients.clear();
}
