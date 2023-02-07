CC := gcc
CFLAGS := -O3 -lX11 

SRCS := $(wildcard src/*.c)

BINARY := xdvd
RM := rm

all: $(BINARY)

$(BINARY):
	$(CC) $(CFLAGS) $(SRCS) -o $(BINARY)

clean:
	$(RM) $(BINARY)