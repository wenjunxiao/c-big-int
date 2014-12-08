CC = gcc
CFLAGS = -O2 -Wall -g

PROG = calc_big_int
OBJS = $(PROG).o big_int.o

all: $(PROG)
	@echo >/dev/null

$(PROG): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS) 

test: $(PROG)
	@./test_big_int.sh ./$(PROG) test_cases.txt
