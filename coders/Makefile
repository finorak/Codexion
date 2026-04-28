NAME = codexion

SRC = main.c arg_utils.c debug.c ft_utils.c \
	  init.c stack.c free_memory.c \
	  thread.c codexion.c bench.c \
	  codexion_utils.c dongle_manager.c \
	  monitoring.c coder_utils.c \
	  manager.c

OBJS = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

PTHREAD = -pthread

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(PTHREAD) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re clean all fclean
