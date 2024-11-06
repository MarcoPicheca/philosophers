NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c utils.c timing.c supervisor.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@echo "compiling..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -lpthread $(OBJECTS) -o $(NAME)

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re