CC = clang
CFLAGS = -g -O0
LDLIBS = -lgc

OBJS = print.o object.o parser.o lexer.o intern.o primitive.o eval.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJS) -o Kiret

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.c parser.h: parser.y
	bison --defines=parser.h -o parser.c parser.y

eval.o: eval.h object.h

print.o: print.h object.h

object.o: object.h intern.h

intern.o: object.h intern.h

lexer.o: parser.h

parser.o: object.h print.h eval.h

clean:
	rm -rf *.o
	rm parser.c
	rm parser.h
	rm lexer.c
	rm Kiret
