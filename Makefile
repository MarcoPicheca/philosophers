NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = src/main.c utils/utils.c src/print_num.c src/init.c src/routine.c \
		src/sleep.c src/eating.c src/routine_sv.c \

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@echo "compiling..."
	@$(CC) $(CFLAGS) -lpthread $(OBJECTS) -o $(NAME) -s

clean:
	@echo "cleaning..."
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re