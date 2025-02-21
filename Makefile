##
## EPITECH PROJECT, 2025
## MyFTP
## File description:
## makefile
##

SRC = src/main.c \
		src/utils/str_to_word_array.c \
		src/Parser/handle_commands.c \
		src/Parser/structure_init.c \
		src/Parser/commands/cdup_command.c \
		src/Parser/commands/cwd_command.c \
		src/Parser/commands/password_command.c \
		src/Parser/commands/port_command.c \
		src/Parser/commands/quit_command.c \
		src/Parser/commands/user_command.c \
		src/Parser/commands/test_command.c \
		src/Core/client/add_client.c \
		src/Core/client/remove_client.c \
		src/Core/client/find_client.c \
		src/Core/server.c \

OBJ = $(SRC:.c=.o)

NAME = myftp

CFLAGS = -Wall -Werror -Wextra -I./include -g

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(SRC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
