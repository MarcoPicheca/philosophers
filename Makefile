NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = src/main.c utils/utils.c src/print_num.c src/init.c src/routine.c \
		src/sleep.c src/eating.c src/routine_sv.c \

all: $(NAME)

$(NAME): $(SRC)
	@echo "compiling..."
	@$(CC) $(CFLAGS) -lpthread $(SRC) -o $(NAME) -s	

clean:
	@echo "cleaning..."

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re