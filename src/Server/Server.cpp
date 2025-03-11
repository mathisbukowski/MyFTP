#include "Server.hpp"

ftp::Server::Server(int port, std::string path)
{
    _port = port;
    _rootPath = path;
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
            client.setRootPath(_rootPath);
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

int ftp::Server::run()
{
    if (_socketServer == -1){
        perror("socket");
        return 84;
    }
    if (inet_pton(AF_INET, LOCALHOST, &_serverAddr.sin_addr) != 1){
        perror("inet_pton");
        return 84;
    }
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port);
    if (bind(_socketServer, (sockaddr *)&_serverAddr, sizeof(_serverAddr)) == -1) {
        perror("bind");
        return 84;
    }
    if (listen(_socketServer, MAX_CLIENTS) == -1){
        perror("listen");
        return 84;
    }
    this->clientManagement();
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
        if (ret == -1)
            break;
        if (_fds[0].revents & POLLIN) {
            sockaddr_in clientAddr = {};
            socklen_t clientAddrLen = sizeof(clientAddr);
            const int clientSocket = accept(_socketServer,
                reinterpret_cast<struct sockaddr *>(&clientAddr),
                &clientAddrLen);
            if (clientSocket == -1)
                continue;
            _fds.push_back({ clientSocket, POLLIN, 0 });
            _nfds += 1;
            this->addNewClient(clientSocket, clientAddr);
            dprintf(clientSocket, "220 Service ready for new user.\r\n");
        }
        this->handleClientInput();
    }
}

void ftp::Server::handleClientDisconnection(int client_socket)
{
    close(client_socket);
    this->removeClient(client_socket);
    _fds.erase(std::remove_if(_fds.begin(), _fds.end(),
        [&](const pollfd &pfd) { return pfd.fd == client_socket; }),
        _fds.end());
    _nfds = _fds.size();
}

std::string ftp::Server::getCommand(const char* buffer)
{
    std::string command = buffer;
    size_t pos = command.find(' ');
    if (pos != std::string::npos) {
        command = command.substr(0, pos);
    }
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    return command;
}

std::string ftp::Server::getArgs(const char *buffer)
{
    std::string command = buffer;
    size_t pos = command.find(' ');
    if (pos == std::string::npos || pos == command.length() - 1) {
        return "";
    }
    std::string args = command.substr(pos + 1);
    if (args.front() == '"' && args.back() == '"') {
        args = args.substr(1, args.size() - 2);
    }
    return args;
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
                this->handleClientDisconnection(_fds[i].fd);
            } else {
                this->handleBuffer(buffer);
                std::cout << "Command: " << this->getCommand(buffer) << "$" << std::endl;
                std::cout << "Args: " << this->getArgs(buffer) << "$" << std::endl;
                std::unique_ptr<ICommand> cmd = commandHandler.handleCommand(this->getCommand(buffer));
                if (cmd) {
                    cmd->execute(this->getArgs(buffer), *this->getClient(_fds[i].fd));
                } else {
                    dprintf(this->getClient(_fds[i].fd)->getSocket(), "500 Unknown command.\r\n");
                }
            }
        }
    }
}

void ftp::Server::handleBuffer(char *buffer)
{
    if (!buffer)
        return;
    while (*buffer == ' ' || *buffer == '\t')
        buffer++;
    char *src = buffer, *dst = buffer;
    bool lastWasSpace = false;
    while (*src) {
        if (*src == ' ' || *src == '\t') {
            if (!lastWasSpace) {
                *dst++ = ' ';
                lastWasSpace = true;
            }
        } else if (*src != '\r' && *src != '\n') {
            *dst++ = *src;
            lastWasSpace = false;
        }
        src++;
    }
    if (dst > buffer && *(dst - 1) == ' ')
        dst--;
    *dst = '\0';
}

ftp::Server::~Server()
{
    if (_socketServer != -1)
        close(_socketServer);
    _fds.clear();
    _clients.clear();
}