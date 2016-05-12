TARGET = expr

all: lemon ${TARGET}

lemon: lemon.c
	gcc -o $@ $<

${TARGET}: ${TARGET}_p.o ${TARGET}_l.o main.o
	g++ -o $@ $^

main.o: main.cpp
	g++ -c -o $@ $<

${TARGET}_l.o: ${TARGET}_l.cpp
	g++ -c -o $@ $<

${TARGET}_l.cpp: expr.l
	flex -o $@  $<

${TARGET}_p.o: ${TARGET}_p.cpp
	g++ -c -o $@ $<

${TARGET}_p.cpp: expr.y
	./lemon -Tlempar.c $<
	mv ${TARGET}.c $@
	mv ${TARGET}.h tokens.h

clean:
	rm -f *.o
	rm -f ${TARGET}_l.cpp
	rm -f ${TARGET}_l.h
	rm -f ${TARGET}_p.cpp
	rm -f tokens.h
	rm -f ${TARGET}.exe
	rm -f ${TARGET}
	rm -f lemon.exe
	rm -f ${TARGET}.out
	rm -f ${TARGET}.c
	rm -f ${TARGET}.h
