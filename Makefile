PROG = main
IFLAG = -Iinclude/
WFLAGS = 
SRCDIR = src/
OBJDIR = obj/
TESTDIR = unit-tests/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))

ifeq (tests, $(firstword $(MAKECMDGOALS)))
TEST_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
$(eval $(TEST_ARGS):;@:)
endif

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(IFLAG) $(WFLAGS) $(OBJS)

$(OBJDIR)%.o:
	$(CC) -c $(IFLAG) $(WFLAGS) $(SRCDIR)%.c

.PHONY: test
tests: $(OBJS)
	$(CC) -o tests $(TESTDIR)tests.c $(IFLAG) $(OBJS)
	@clear
	./tests $(TEST_ARGS)

clean:
	rm -rf $(PROG) tests