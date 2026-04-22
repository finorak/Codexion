CC = cc
FLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
NAME = codexion
NORMINETT = norminette
OBJ = $(SRCS:.c=.o)
VALGRIND = valgrind -s --track-origins=yes --leak-check=full
SRCS = main.c \
	   data_seter/codexion.c \
	   data_seter/init.c \
	   data_seter/stack.c \
	   data_seter/join_thread.c \
	   utils/arg_checker.c \
	   utils/free_memory.c

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(PTHREAD) $(OBJ) -o $(NAME)

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
