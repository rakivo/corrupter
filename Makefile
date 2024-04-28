CC = gcc
WIN_CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb

BIN = corruptor
SRC = main.c
HEADERS = main.h
OBJS = main.o
WIN_OBJS = main.win.o

all: $(BIN) $(BIN).exe objs_clean

linux: $(BIN) objs_clean
win: $(BIN).exe objs_clean

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BIN).exe: $(WIN_OBJS)
	$(WIN_CC) $(CFLAGS) $(WIN_OBJS) -o $@

$(OBJS): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC) -o $@

$(WIN_OBJS): $(SRC) $(HEADERS)
	$(WIN_CC) $(CFLAGS) -c $(SRC) -o $@

objs_clean:
	rm -f $(OBJS) $(WIN_OBJS)

clean:
	rm -f $(OBJS) $(WIN_OBJS) $(BIN) $(BIN).exe

.PHONY: all clean
