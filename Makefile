CC = gcc
CFLAGS = -Iinc -Wall -Wextra -g
SRCS = src/main.c src/db.c src/users.c src/sqlite3.c
OBJS = $(SRCS:.c=.o)
TARGET = bank

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -ldl -lpthread

clean:
	rm -f $(OBJS) $(TARGET)
