/*
 * Util.h
 *
 *  Created on: Mar 29, 2009
 *      Author: ivan_deras
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <sstream>
#include <list>
#include <string>
#include "Expression.h"

using namespace std;

/* Added */
struct TokenInfo {
    int tokenType;
    string strValue;
    int intValue;
    ExpressionOperator	oper;

    TokenInfo(int tokenType, string strValue) {
        this->tokenType = tokenType;
        this->strValue = strValue;
    }
};

struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};
////////////////

/*
 * Libera una lista.  El tipo T debe ser un apuntador.
 */
template <typename T>
void inline FreeList(list<T> *l)
{
	typename list<T>::iterator it = l->begin();

	while (it != l->end()) {
		T element = *it;

		delete element;

		it++;
	}
	l->clear();
}

/*
 * Convierte una lista a string.  El tipo T debe ser un apuntador a una clase.
 * Ademas la clase debe tener un metodo ToString.
 */
template <typename T>
string inline ListToString(list<T> *l, string separator, bool include_last_separator)
{
	typename list<T>::iterator it = l->begin();
	ostringstream out;

	while (it != l->end()) {
		T element = *it;

		out << element->ToString();

		it++;

		if (it != l->end())
			out << separator;
		else if (include_last_separator)
			out << separator;
	}

	return out.str();
}

template <typename T>
string convertToString(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

typedef struct YYLTYPE YYLTYPE;

int GetNextChar(char *b, int maxBuffer);
void BeginToken(char *t, struct YYLTYPE *yylloc);

string getTokenString(int token, TokenInfo *info);
TokenInfo *allocTokenInfo(int tokenType, string strValue);
void freeTokenInfo(TokenInfo *ti);
void reportError(const char *format, ...);

#endif /* UTIL_H_ */
