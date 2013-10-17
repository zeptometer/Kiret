CC = clang
CFLAGS = -g -O0
LDLIBS = -lgc
TEST_OBJS = test.o print.o object.o

all: test

test: $(TEST_OBJS)

test.c: print.h object.h

print.c: print.h object.h

object.c: object.h
