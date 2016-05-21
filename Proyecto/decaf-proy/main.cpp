#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "ClassDef.h"

extern ifstream in;
extern int current_line;

static int errors = 0;

using namespace std;

//int yyparse();
int nextToken(struct TokenInfo *&p_info);

ClassDef *class_def;
string getTokenString(int token, TokenInfo *info);

int main(int argc, char *argv[])
{
/*	cout <<  "Param: " << argc << endl;
	cout << argv[0] << endl;
	cout << argv[1] << endl; */
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
//	yyparse();
	cout << "BEFORE"<<endl;
	if (errors == 0) {
		cout<<"IN"<<endl;
		if (class_def != NULL)
			cout << class_def->ToString() << endl;
		else
			cout << "No hay contenido" << endl;
	}
	cout << "AFTER"<<endl;
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
