CC = gcc
CFLAGS = -Wall -Wextra -Werror -O0 -g -fsanitize=address	

NAME_GNL = test_gnl
OBJ_GNL = slist.o get_next_line.o test_gnl.o
SRC_GNL = $(OBJ_GNL:.o=.c)

NAME_GNB = test_gnb
OBJ_GNB = get_next_byte.o test_gnb.o
SRC_GNB = $(OBJ_GNB:.o=.c)

all: $(NAME_GNL) $(NAME_GNB)

$(NAME_GNL): $(OBJ_GNL)
	$(CC) -o $(NAME_GNL) $^ $(CFLAGS)

$(NAME_GNB): $(OBJ_GNB)
	$(CC) -o $(NAME_GNB) $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(OBJ_GNL) $(OBJ_GNB)

fclean: clean
	rm -f $(NAME_GNL) $(NAME_GNB)

re: fclean all

norminette:
	norminette get_next_line.h slist.h get_next_line.c slist.c \
				get_next_byte.h get_next_byte.c
