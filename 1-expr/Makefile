all: expr

expr: expr_lexer.o expr_parser.o
	g++ -o $@ $^

expr_lexer.o: expr_lexer.cpp
	g++ -c -o $@ $<

expr_lexer.cpp: expr.l
	flex -o $@ $<

expr_parse.o: expr_parser.cpp
	g++ -c -o $@ $<

clean:
	rm -f *.o
	rm -f expr_lexer.cpp
	rm -f expr
