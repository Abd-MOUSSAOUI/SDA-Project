PROG = main
CC = clang
OBJS = main.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) -g $(OBJS)

main.o:
	$(CC) -c main.c

clean:
	rm -rf $(PROG) $(OBJS)