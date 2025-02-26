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
    _rootPath = path;
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    _serverAddr = {};
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

void ftp::Server::addNewClient(int client_socket)
{
    _clients.emplace_back(client_socket);
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
    if (_socketServer == -1 || this->checkPath(_rootPath) == 84 || this->checkPort(_port) == 84 || inet_pton(AF_INET, LOCALHOST, &_serverAddr.sin_addr) != 1)
        throw ServerError("Error: Invalid arguments.");
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port);
    if (bind(_socketServer, (sockaddr *)&_serverAddr, sizeof(_serverAddr)) == -1)
        throw ServerError("Error: bind failed");
    if (listen(_socketServer, 10) == -1)
        throw ServerError("Error: listen failed");
    std::cout << "Server started on port " << _port << std::endl;
    clientManagement();
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
    int nfds = 1;
    int ret = 0;

    _fds[0].fd = _socketServer;
    _fds[0].events = POLLIN;
    while (1) {
        ret = poll(_fds, nfds, -1);
        if (ret == -1) {
            dprintf(_socketServer, "Error: poll failed\n");
            break;
        }
        std::cout << "Polling..." << std::endl;
        if (_fds[0].revents & POLLIN) {
            sockaddr_in serverAddr = this->getServerAddr();
            size_t serverAddrLen = sizeof(serverAddr);
            const int clientSocket = accept(_socketServer,
                reinterpret_cast<struct sockaddr *>(&serverAddr), reinterpret_cast<socklen_t *>(&serverAddrLen));
            if (clientSocket == -1) {
                dprintf(clientSocket, "Error: accept failed\n");
                continue;
            }
            _fds[nfds].fd = clientSocket;
            _fds[nfds].events = POLLIN;
            nfds += 1;
            addNewClient(clientSocket);
            std::cout << "New client connected : " << clientSocket << std::endl;
        }
        handleClientInput(_fds, &nfds);
    }
}

void ftp::Server::handleClientDisconnection(pollfd* fds, int* nfds, int *i)
{
    std::cout << "Client disconnected : " << fds[*i].fd << std::endl;
    close(fds[*i].fd);
    removeClient(fds[*i].fd);
    for (int j = (*i); j < *nfds - 1; j++)
        fds[j] = fds[j + 1];
    (*nfds)--;
    (*i)--;
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

void ftp::Server::handleClientInput(pollfd* fds, int* nfds)
{
    ftp::CommandHandler commandHandler;

    for (int i = 1; i < *nfds; i++) {
        if (fds[i].revents & POLLIN) {
            char buffer[1024] = {};
            ssize_t bytes = read(fds[i].fd, buffer, sizeof(buffer));
            if (bytes == -1) {
                std::cout << "Error: read failed" << std::endl;
                return;
            }
            if (bytes == 0) {
                handleClientDisconnection(fds, nfds, &i);
            } else {
                cleanBuffer(buffer);
                std::string command = getCommand(buffer);
                std::string args = getArgs(buffer);
                std::unique_ptr<ICommand> cmd = commandHandler.handleCommand(command, *getClient(fds[i].fd));
                if (cmd) {
                    std::cout << "Command found" << std::endl;
                    cmd->execute(args, *getClient(fds[i].fd));
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
    close(_socketServer);
}
