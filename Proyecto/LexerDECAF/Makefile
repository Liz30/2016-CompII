DECAF_LEXER 	:= decaf_lexer.cpp
DECAF_GRAMMAR	:= decaf_grammar.cpp
DECAF_TOKENS	:= decaf_tokens.h
DECAF_EXE := decaf.exe
TARGET  := decaf
SRCS    := ${DECAF_LEXER} Expression.cpp Statement.cpp Util.cpp main.cpp
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

${DECAF_LEXER}:	decaf_lexer.l
	flex -o $@ $<

clean::
	-rm -f *~ *.o ${TARGET} ${DECAF_LEXER} ${DECAF_GRAMMAR} ${DECAF_TOKENS} ${DECAF_EXE} decaf_grammar.out
	rm -f ${TARGET}_grammar.c
