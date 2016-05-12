TARGET = scalc

all: lemon ${TARGET}

lemon: lemon.c
	gcc -o $@ $<

${TARGET}: ${TARGET}_p.o ${TARGET}_l.o
	g++ -o $@ $^

${TARGET}_l.o: ${TARGET}_l.cpp
	mv lex.cpp $<
	g++ -c -o $@ $<

${TARGET}_l.cpp: ${TARGET}.l
	flex -o $@ --header-file=${TARGET}_l.h $<

${TARGET}_p.o: ${TARGET}_p.cpp
	g++ -c -o $@ $<

${TARGET}_p.cpp: ${TARGET}.y
	./lemon -Tlempar.c $<
	mv ${TARGET}.c $@

clean:
	rm -f *.o
	rm -f ${TARGET}_l.cpp
	rm -f ${TARGET}_l.h
	rm -f ${TARGET}_p.cpp
	rm -f ${TARGET}.exe
	rm -f ${TARGET}
	rm -f lemon.exe
	rm -f ${TARGET}.out
	rm -f ${TARGET}.c
	rm -f ${TARGET}.h
