CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = $(wildcard *.c)
HDRS = philo.h
TARGET = philo
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(wildcard *.o)

re: clean all

fclean: clean
	rm -f $(TARGET)

.PHONY: all clean re fclean