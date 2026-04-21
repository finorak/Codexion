CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = codexion
NORMINETT = norminette
OBJ = $(SRCS:.c=.o)
VALGRIND = valgrind -s --track-origins=yes --leak-check=full
SRCS = main.c \
	   utils/coders.c \
	   utils/stack_utils.c \
	   utils/parsing.c \
	   utils/error_handling/arg_error.c \
	   utils/memory_management/free_coders.c

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	./$(NAME) 3 500 300 400 200 3 500 fifo

lint:
	$(NORMINETT) $(SRCS)

debug:
	$(VALGRIND) ./$(NAME) 5 500 300 400 200 3 500 fifo

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean re clean all lint debug
