CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

NAME = test
OBJ = slist.o get_next_line.o main.o
SRC = $(OBJ:.o=.c)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norminette:
	norminette get_next_line.h slist.h get_next_line.c slist.c
