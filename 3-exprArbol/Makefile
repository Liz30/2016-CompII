all: expr

expr: arbol.o expr_p.o expr_l.o 
	g++ -o $@ $^

arbol.o: arbol.cpp arbol.h
	g++ -c -o $@ $<

expr_l.o: expr_l.cpp
	g++ -c -o $@ $<

expr_l.cpp: expr.l
	flex -o $@ $<

expr_p.o: expr_p.cpp
		g++ -c -o $@ $<

expr_p.cpp: expr.y
	bison --defines=tokens.h -o $@ $<


clean:
	rm -f *.o
	rm -f expr_l.cpp
	rm -f expr_p.cpp
	rm -f tokens.h
	rm -f expr.exe
	rm -f expr
