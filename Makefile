PROG = main
CC = clang
IFLAG = -Iinclude/
WFLAGS = 
SRCDIR = src/
OBJDIR = obj/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(IFLAG) $(WFLAGS) $(OBJS)

$(OBJDIR)%.o:
	$(CC) -c $(IFLAG) $(WFLAGS) $(SRCDIR)%.c

clean:
	rm -rf $(PROG)