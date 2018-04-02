PROG = main
IFLAG = -Iinclude/
WFLAGS = 
SRCDIR = src/
OBJDIR = obj/
TESTDIR = unit-tests/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
TESTSRCS = $(wildcard unit-tests/*.c)
TESTOBJS = $(patsubst unit-tests/*.c, obj/*.o, $(TESTSRCS))

ifeq (tests, $(firstword $(MAKECMDGOALS)))
TEST_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
$(eval $(TEST_ARGS):;@:)
endif

$(OBJDIR)%.o:
	$(CC) -c $(IFLAG) $(WFLAGS) $(SRCDIR)%.c

.PHONY: test
tests: $(OBJS) $(TESTOBJS)
	$(CC) -o tests $(IFLAG) $(OBJS) $(TESTOBJS)
	@clear
	./tests $(TEST_ARGS)
	rm tests

$(TESTDIR)%.o:
	$(CC) -c $(WFLAGS) $(TESTDIR)%.c

clean:
	rm -rf $(PROG) tests