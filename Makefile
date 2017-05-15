# Makefile
VERSION = 3.02
CC      = /usr/bin/gcc
OBJ	 = sasc.o gpib-functions.o callback.o widget.o callback-gpib.c
CFLAGS  = -Wall -ggdb
LDFLAGS = -lgpib -lm `pkg-config --cflags --libs gtk+-2.0`
PRG 	= sasc
all: $(OBJ)
	$(CC) $(CFLAGS) -o $(PRG) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

clean:
	rm -f $(PRG) *~ *.o a.out *.png *.csv

install:
	sudo cp $(PRG) /usr/local/bin

uninstal:
	cd /usr/local/bin
	sudo rm -f $(PRG)
