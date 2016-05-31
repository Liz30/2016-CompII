DECAF_LEXER 	:= decaf_lexer.cpp
DECAF_GRAMMAR	:= decaf_grammar.cpp
DECAF_TOKENS	:= decaf_tokens.h
DECAF_EXE := decaf.exe
TARGET  := decaf
SRCS    := ${DECAF_LEXER} ${DECAF_GRAMMAR} Expression.cpp Statement.cpp Util.cpp main.cpp
OBJS    := ${SRCS:.cpp=.o}

CCFLAGS = -g
LDFLAGS =
LIBS    =

.PHONY: all clean

all:: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS}

${OBJS}: %.o: %.cpp
	${CXX} ${CCFLAGS} -o $@ -c $<

${DECAF_LEXER}:	decaf_lexer.l ${DECAF_TOKENS}
	flex -o $@ $<

${DECAF_GRAMMAR} ${DECAF_TOKENS}: decaf_grammar.y
	lemon -q -Tlempar.c $<
	mv ${TARGET}_grammar.c ${DECAF_GRAMMAR}
	mv ${TARGET}_grammar.h ${DECAF_TOKENS}

clean::
	-rm -f *~ *.o ${TARGET} ${DECAF_LEXER} ${DECAF_GRAMMAR} ${DECAF_TOKENS} ${DECAF_EXE} decaf_grammar.output
	rm -f ${TARGET}_grammar.c
	rm -f ${TARGET}_grammar.h
	rm -f ${TARGET}_grammar.out
