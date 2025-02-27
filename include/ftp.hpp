/*
** EPITECH PROJECT, 2025
** NWP-400
** File description:
** 02
*/

#ifndef FTP_HPP
    #define FTP_HPP

    #include <iostream>
    #include <string>
	#include <vector>
    #include <fstream>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <poll.h>
	#include <unistd.h>
	#define LOCALHOST "127.0.0.1"
	#define LENGTH_COMMANDS 20

namespace ftp {
	class Server;
	class Client;
	class CommandHandler;
	class PwdCommand;
	class UserCommand;
	class PasswordCommand;
	class QuitCommand;
	class CwdCommand;
	class CdupCommand;
	class HelpCommand;
	class NoopCommand;
	class PortCommand;

	class ICommand {
	public:
		virtual ~ICommand() = default;
		virtual void execute(std::string args, Client &client) = 0;
	};
};


#endif //FTP_HPP
