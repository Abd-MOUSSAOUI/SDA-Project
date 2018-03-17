PROG = main
CC = clang
SRCDIR = src/
OBJDIR = obj/
OBJS = $(OBJDIR)main.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) -g $(OBJS)

$(OBJDIR)main.o:
	$(CC) -c $(SRCDIR)main.c
	mv main.o $(OBJDIR)main.o

clean:
	rm -rf $(PROG) $(OBJS)