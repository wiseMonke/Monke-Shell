CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRCS = src/main.c src/shell.c src/commands.c src/utils.c
OBJS = $(SRCS:.c=.o)
TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
