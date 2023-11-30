CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.o ctrlgpio.o motor.o rcController.o
	$(CC) $(CFLAGS) -o main main.o ctrlgpio.o motor.o rcController.o -lncurses

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

ctrlgpio.o: ctrlgpio.c
	$(CC) $(CFLAGS) -c ctrlgpio.c

motor.o: motor.c
	$(CC) $(CFLAGS) -c motor.c

rcController.o: rcController.c
	$(CC) $(CFLAGS) -c rcController.c

clean:
	rm -f main main.o ctrlgpio.o motor.o rcController.o
