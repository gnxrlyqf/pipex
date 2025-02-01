CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I./includes
SRC = $(wildcard src/*.c)
NAME = pipex

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) $(SRC:.c=.o) $(INC) -o $(NAME)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.c=.o)

fclean: clean
	rm -rf $(NAME)

re: fclean all