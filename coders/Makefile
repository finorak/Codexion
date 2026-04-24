CC = cc
FLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
NAME = codexion
NORMINETT = norminette
OBJ = $(SRCS:.c=.o)
VALGRIND = valgrind --tool=helgrind
SRCS = main.c \
	   data_seter/codexion.c \
	   data_seter/init.c \
	   data_seter/stack.c \
	   data_seter/join_thread.c \
	   simulate/coder.c \
	   utils/arg_checker.c \
	   utils/free_memory.c \
	   utils/bench.c \
	   simulate/dongle_manager.c \
	   simulate/scheduling.c \
	   wait_lst_manager/stack.c

HEADERS = codexion.h

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME):$(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(PTHREAD) $(OBJ) -o $(NAME)

lint:
	$(NORMINETT) $(SRCS) $(HEADERS)

debug:
	$(VALGRIND) ./$(NAME) 3 500 300 400 200 3 500 fifo

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean re clean all lint debug
