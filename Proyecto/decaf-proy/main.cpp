#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "ClassDef.h"

extern ifstream in;
extern int current_line;

static int errors = 0;

using namespace std;

int yyparse();
int nextToken(struct TokenInfo *&p_info);

ClassDef *class_def;

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
	yyparse();

	if (errors == 0) {
		cout << class_def->ToString() << endl;
	}

	return 0;
}

void yyerror(const char *message)
{
	errors++;

	fprintf(stderr, "%d:%s\n", current_line, message);
}
