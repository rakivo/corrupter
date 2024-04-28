CC = gcc
WIN_CC = cl
WIN_CROSS_CC = x86_64-w64-mingw32-gcc

CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb

BIN = corruptor
SRC = main.c
HEADERS = main.h

OBJS = main.o
WIN_OBJS = main.win.o
WIN_OBJS_CROSS = main.win_cross.o

all: unix win_cross objs_clean

unix: $(BIN)

win: $(BIN).exe

win_cross: $(BIN)_cross.exe

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BIN).exe: $(WIN_OBJS)
	$(WIN_CC) $(CFLAGS) $(WIN_OBJS) -o $@

$(WIN_OBJS): $(SRC) $(HEADERS)
	$(WIN_CC) $(CFLAGS) -c $(SRC) -o $@

$(BIN)_cross.exe: $(WIN_OBJS_CROSS)
	$(WIN_CROSS_CC) $(CFLAGS) $(WIN_OBJS_CROSS) -o $@

$(WIN_OBJS_CROSS): $(SRC) $(HEADERS)
	$(WIN_CROSS_CC) $(CFLAGS) -c $(SRC) -o $@

objs_clean:
	rm -f $(OBJS) $(WIN_OBJS) $(WIN_OBJS_CROSS)

clean:
	rm -f $(OBJS) $(WIN_OBJS) $(WIN_OBJS_CROSS) $(BIN) $(BIN).exe $(BIN)_cross.exe

.PHONY: all clean objs_clean
