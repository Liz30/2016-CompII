TARGET=expr
CPP_SOURCES = ast.cpp expr_parser.cpp expr_lexer.cpp main.cpp
HEADERS = tokens.h lexer_util.h ast.h
OBJ = ${CPP_SOURCES:.cpp=.o}

all: ${TARGET}

.PHONY: test clean

${TARGET}: ${OBJ}
	g++ -o $@ $^


%.o : %.c
	g++ -c -o $@ $<

${TARGET}_lexer.cpp: expr.l
	flex -o $@ $<

${TARGET}_parser.cpp: expr.y
	lemon -q -Tlempar.c $<
	mv expr.c $@
	mv expr.h tokens.h

clean:
	rm -f *.o
	rm -f ${TARGET}_lexer.cpp
	rm -f ${TARGET}_parser.cpp
	rm -f tokens.h
	rm -f expr.out
	rm -f ${TARGET}

test:
	./${TARGET} < tests/test1.txt
