CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I./includes
SRC = $(wildcard src/*.c)
BONUS = $(wildcard bonus/*.c)
NAME = pipex

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: $(NAME:=_bonus)

$(NAME): $(SRC:.c=.o)
	$(CC) $^ $(INC) -o $(NAME)

$(NAME:=_bonus): $(BONUS:.c=.o)
	$(CC) $^ $(INC) -o $(NAME:=_bonus)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.c=.o) $(BONUS:.c=.o)

fclean: clean
	rm -rf $(NAME) $(NAME:=_bonus)

re: fclean all