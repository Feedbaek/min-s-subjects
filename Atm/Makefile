CC = gcc

CFLAGS = -Wall -Wextra -Werror
DICSRCS = srcs
DICHEADER = include

TARGET = atm
SRCS = $(wildcard $(DICSRCS)/*.c)
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(DICHEADER)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

all: $(TARGET)

clean:
	rm -f $(DICSRCS)/*.o

fclean: clean
	rm -f $(TARGET)

re: fclean all
	./$(TARGET)
