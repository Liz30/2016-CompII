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

using namespace std;

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

struct YYLTYPE;

int GetNextChar(char *b, int maxBuffer);
void BeginToken(char *t, struct YYLTYPE *yylloc);

#endif /* UTIL_H_ */
