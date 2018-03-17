PROG = main
CC = clang
IFLAG = -Iinclude/
SRCDIR = src/
OBJDIR = obj/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))

# SRC = $(wildcard src/*.cpp)
# OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(IFLAG) $(OBJS)

$(OBJDIR)%.o:
	$(CC) -c $(IFLAG) $(SRCDIR)%.c
	# mv main.o $(OBJDIR)main.o

clean:
	rm -rf $(PROG)