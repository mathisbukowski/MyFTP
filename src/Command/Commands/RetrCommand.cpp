/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** 03
*/

#include "RetrCommand.hpp"
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>

ftp::RetrCommand::RetrCommand()
{
}

void ftp::RetrCommand::execute(std::string args, Client& client)
{
    if (!client.isLoggedIn()) {
        dprintf(client.getSocket(), "530 Not logged in.\r\n");
        return;
    }
    if (args.empty()) {
        dprintf(client.getSocket(), "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    std::filesystem::path filePath = client.getCwd() / args;
    if (!exists(filePath) || !is_regular_file(filePath)) {
        dprintf(client.getSocket(), "550 File does not exist.\r\n");
    }
    int data_socket = client.getDataSocket();
    if (data_socket == -1) {
        dprintf(client.getSocket(), "425 Use PORT or PASV first.\r\n");
        return;
    }
    dprintf(client.getSocket(), "150 File status okay; about to open data connection.\r\n");

    pid_t pid = fork();
    if (pid == -1) {
        // En cas d'erreur de fork
        dprintf(client.getSocket(), "550 Internal error, could not create process.\r\n");
        return;
    }

    if (pid == 0) {
        // Code du processus enfant (envoyer le fichier)
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            dprintf(client.getSocket(), "550 Failed to open file.\r\n");
            exit(1);  // Quitter l'enfant avec une erreur
        }

        // Lire le fichier et l'envoyer via le socket de données avec write()
        char buffer[4096]; // Buffer pour le transfert du fichier
        ssize_t bytesRead;
        while ((bytesRead = file.readsome(buffer, sizeof(buffer))) > 0) {
            ssize_t bytesWritten = write(data_socket, buffer, bytesRead);
            if (bytesWritten == -1) {
                dprintf(client.getSocket(), "550 Failed to send file.\r\n");
                close(data_socket);
                exit(1); // Quitter l'enfant en cas d'erreur de transmission
            }
        }
        file.close();
        close(data_socket);  // Fermer la connexion de données

        // Terminer le processus enfant
        exit(0);
    } else {
        // Code du processus parent (juste gérer les réponses de statut)
        int status;
        waitpid(pid, &status, 0);  // Attendre que l'enfant termine

        // Une fois le transfert terminé, répondre au client
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            dprintf(client.getSocket(), "226 Closing data connection.\r\n");
        } else {
            dprintf(client.getSocket(), "550 Failed to transfer file.\r\n");
        }

        // Réinitialiser le socket de données
        client.setDataSocket(-1);
    }
}

