# Makefile for ex1-q1 winter 2019A
CFLAGS = -Wall
LDFLAGS  = -lm  # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex1_q1


all: $(PROG) test 

ex1_q1.o: ex1_q1.c
	${ECHO}
	${CC} ${CFLAGS} -c ex1_q1.c

ex1_q1: ex1_q1.o
	echo 'going to link ex1_q1...'
	${CC} -o ex1_q1 -Wall ex1_q1.o

test:${PROG}
	@echo going to run test...
	./$(PROG) < in.txt > out.log


clean:
	rm -vf *.o ${PROG} *.log