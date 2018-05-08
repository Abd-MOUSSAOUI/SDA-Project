PROG = main
IFLAG = -Iinclude/
SRCDIR = src/
OBJDIR = obj/
TESTDIR = unit-tests/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/*.c, obj/*.o, $(SRCS))
TESTSRCS = $(wildcard unit-tests/*.c)
TEST_OBJS = $(patsubst unit-tests/*.c, obj/*.o, $(TESTSRCS))

ifeq (tests, $(firstword $(MAKECMDGOALS)))
TEST_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
$(eval $(TEST_ARGS):;@:)
endif

ifdef SILENT
.SILENT:
endif

ifdef DEBUG
DEFINES = -DDEBUG
endif

$(OBJDIR)%.o:
	$(CC) -c $(IFLAG) $(WFLAGS) $(SRCDIR)%.c $(DEFINES)

.PHONY: test
tests: $(OBJS) $(TEST_OBJS)
	@rm -rf $(PROG) tests tests.dSYM
	$(CC) -o tests -g $(IFLAG) $(OBJS) $(TEST_OBJS) $(DEFINES)
	# @./tests $(TEST_ARGS)
	# @rm tests

$(TESTDIR)%.o:
	$(CC) -c $(WFLAGS) $(TESTDIR)%.c $(DEFINES)

clean:
	@rm -rf $(PROG) tests tests.dSYM