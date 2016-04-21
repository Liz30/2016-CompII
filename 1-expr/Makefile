all: expr

expr: expr.o
	g++ -o $@ $^

expr.o: expr.cpp
	g++ -c -o $@ $<

expr.cpp: expr.l
	flex -o $@ $<

clean:
	rm -f *.o
	rm -f expr.cpp
	rm -f expr.exe
	rm -f expr
