NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c utils.c print_num.c init.c routine.c \
		sleep.c eating.c routine_sv.c \

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@echo "compiling..."
	@$(CC) $(CFLAGS) -lpthread $(OBJECTS) -o $(NAME)

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re