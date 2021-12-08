CC=gcc

SRCS = main.c
NAME = Ramdom_Maze

OBJECTS = $(SRCS:.c=.o)
OBJS = $(OBJECTS)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ -o $@

clean:
	rm -rf $(OBJECTS)

fclean:
	rm -rf $(NAME) $(OBJECTS)

re: fclean all
