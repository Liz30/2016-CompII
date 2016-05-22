#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include "ClassDef.h"
//#include "decaf_tokens.h"
#include "tokens.h"

using namespace std;

extern ifstream in;
extern int current_line;

static int errors = 0;


ClassDef *class_def;
string getTokenString(int token, TokenInfo *info);
int nextToken(struct TokenInfo *&p_info);

extern YYLTYPE *yylloc;
int yylex();
/*void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));
void Parse(void *yyp, int yymajor, TokenInfo *yyminor);*/

set<TokenInfo *> tiSet;

int main(int argc, char *argv[])
{
	if (argc > 0) {
		++argv, --argc; /* El primer argumento es el nombre del programa */
		in.open(argv[0], ifstream::in|ifstream::binary);

		if (!in.is_open()) {
			cerr << "No se pudo abrir el archivo " << argv[0] << endl << endl;
			return 0;
		}
	}
	else {
		cerr << "Uso: " << argv[0] << " <archivo>" << endl << endl;
		return 0;
	}

	class_def = 0;
	cout << "1 main"<<endl;
	/* PARSER */
		/*void *parser = ParseAlloc(malloc);
		TokenInfo *ti;

		cout << "2"<<endl;
		int token = nextToken(ti);
		cout << "3 Token: "<<token<<endl;

		while (token != T_EOF) {
				Parse(parser, token, ti);
				cout << "Token: "<<getTokenString(token, ti)<<endl;
				token = nextToken(ti);
		}
		Parse(parser, T_EOF, ti);
		ParseFree(parser, free);*/
	/////////////////////////////////////////////

	int token = yylex();
	cout << "BEFORE"<<endl;
	while ( token != T_EOF ){
			cout<<"Token: "<<token<<endl;
			token = yylex();
	}
	cout<<"Token: "<<token<<endl;
	cout << "fin de while"<<endl;

	if (errors == 0) {
		if (class_def != NULL)
			cout << class_def->ToString() << endl;
		else
			cout << "No hay contenido" << endl;
	}
	return 0;
}

void reportError(const char *format, ...)
{
    va_list args;

    errors++;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
