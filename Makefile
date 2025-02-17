##
## EPITECH PROJECT, 2025
## MyFTP
## File description:
## makefile
##

SRC =	src/main.c

OBJ = $(SRC:.c=.o)

NAME = myftp

CFLAGS = -Wall -Werror -Wextra -I./include

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(SRC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all