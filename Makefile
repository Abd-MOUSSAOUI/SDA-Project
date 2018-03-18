PROG = main
CC = clang
IFLAG = -Iinclude/
SRCDIR = src/
OBJDIR = obj/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(IFLAG) $(OBJS)

$(OBJDIR)%.o:
	$(CC) -c $(IFLAG) $(SRCDIR)%.c

clean:
	rm -rf $(PROG)