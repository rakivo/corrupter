CC = cc
CFLAGS = -Wall -Wextra -Werror -pedantic

BIN = corrupter
SRC = main.c
HEADERS = main.h
OBJS = $(SRC:.c=.o)

all: $(BIN) objs_clean

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

objs_clean:
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(BIN)
