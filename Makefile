##
## EPITECH PROJECT, 2025
## MyFTP
## File description:
## Makefile
##

SRC = src/main.cpp \
		src/Server/Server.cpp \
		src/Client/Client.cpp \
		src/Command/ACommand.cpp \
		src/Command/Commands/PwdCommand.cpp \
		src/Command/Commands/UserCommand.cpp \
		src/Command/Commands/PasswordCommand.cpp \
		src/Command/Commands/QuitCommand.cpp \
		src/Handler/CommandHandler.cpp \


OBJ = $(SRC:.cpp=.o)

NAME = myftp

CFLAGS = -std=c++20 -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(CFLAGS) $(SRC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

