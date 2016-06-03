#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include "ClassDef.h"
#include "decaf_tokens.h"

using namespace std;

extern ifstream in;
extern int current_line;

static int errors = 0;

map<string, ResultValue> vars;
map<string, ResultValue> varsTemp;
map<string, Type> methods;

ClassDef *class_def;
string getTokenString(int token, TokenInfo *info);
int nextToken(struct TokenInfo *&p_info);

extern YYLTYPE *yylloc;

void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));
void Parse(void *yyp, int yymajor, TokenInfo *yyminor);

set<TokenInfo *> tiSet;

TokenInfo *allocTokenInfo(int tokenType, char* strValue)
{
    TokenInfo *ti = new TokenInfo(tokenType, strValue);
    //printf("Alloc: %p\n", ti);
    if (ti != NULL) {
        tiSet.insert(ti);
    }
    return ti;
}


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

	/* PARSER */
		void *parser = ParseAlloc(malloc);
		TokenInfo *ti;// = new TokenInfo;

		int token = nextToken(ti);
		//cout << "BEFORE Token: "<<token<<endl;

		while (token != T_EOF) {
				Parse(parser, token, ti);
        //cout<<" 2 Parser. Token: "<<token<<endl;
				//cout << "Token: ("<<token<<")    "<<getTokenString(token, ti)<<endl;
				token = nextToken(ti);
		}
		Parse(parser, T_EOF, ti);
		ParseFree(parser, free);
	/////////////////////////////////////////////

	if (errors == 0) {
		if (class_def != NULL)
			//cout <<
      class_def->Execute();//  ToString() << endl;
		else
			cout << "No hay contenido" << endl;
	}

  cout<<endl<<"VARS......"<<endl;
  map<string, ResultValue>::iterator iv = vars.begin();
  for (iv; iv!=vars.end(); iv++){
      cout << "  vars[" << iv->first << "] => Tipo: " << iv->second.type << " Valor: ";
      switch (iv->second.type){
        case Int: cout << iv->second.value.int_value << endl; break;
        case Boolean: cout << iv->second.value.bool_value << endl; break;
     }
  }

  cout<<endl<<"TEMP......"<<endl;
  iv = varsTemp.begin();
  for (iv; iv!=varsTemp.end(); iv++){
      cout << "  Temp[" << iv->first << "] => Tipo: " << iv->second.type << " Valor: ";
      switch (iv->second.type){
        case Int: cout << iv->second.value.int_value << endl; break;
        case Boolean: cout << iv->second.value.bool_value << endl; break;
     }
  }

  cout<<endl<<"METHODS......"<<endl;
  map<string, Type>::iterator im = methods.begin();
  for (im; im!=methods.end(); im++)
      cout << "  Temp[" << im->first << "]: " << im->second << endl;

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
