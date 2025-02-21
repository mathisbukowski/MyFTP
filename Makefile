##
## EPITECH PROJECT, 2025
## MyFTP
## File description:
## Makefile
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
	src/Parser/commands/pwd_command.c \
	src/Core/client/add_client.c \
	src/Core/client/remove_client.c \
	src/Core/client/find_client.c \
	src/Core/server.c

NO_MA = src/utils/str_to_word_array.c \
		src/Parser/handle_commands.c \
		src/Parser/structure_init.c \
		src/Parser/commands/cdup_command.c \
		src/Parser/commands/cwd_command.c \
		src/Parser/commands/password_command.c \
		src/Parser/commands/port_command.c \
		src/Parser/commands/quit_command.c \
		src/Parser/commands/user_command.c \
		src/Parser/commands/test_command.c \
		src/Parser/commands/pwd_command.c \
		src/Core/client/add_client.c \
		src/Core/client/remove_client.c \
		src/Core/client/find_client.c \
		src/Core/server.c

SRC_TESTS = tests/test_str_to_word_array.c \
			tests/test_add_client.c \
			tests/test_find_client.c \
			tests/test_remove_client.c \
			tests/test_cdup.c \
			tests/test_cwd.c \
			tests/test_server.c \
			tests/test_password.c \
			tests/test_quit.c \
			tests/test_user.c \
			tests/test_handle_commands.c \
			tests/test_structure_init.c \
			tests/test_pwd_command.c \

OBJ = $(SRC:.c=.o)
OBJ_TESTS = $(SRC_TESTS:.c=.o)

NAME = myftp
TEST_NAME = unit_tests

CFLAGS = -Wall -Werror -Wextra -I./include -g

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(SRC)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_TESTS)
	rm -rf *.gcda
	rm -rf *.gcno

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

tests_run: clean
	gcc -o $(TEST_NAME) $(SRC_TESTS) $(NO_MA) --coverage -lcriterion $(CFLAGS) -Wl,--wrap=malloc
	./$(TEST_NAME) --verbose --full-stats

gcovr_branches:
	gcovr --branches --txt --exclude tests/
