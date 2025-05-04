NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = philo_bonus.c atoi_bonus.c inits_bonus.c utils_bonus.c routine_bonus.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re