/*
 * Variable.h
 *
 *  Created on: Mar 27, 2009
 *      Author: Ivan Deras
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <list>
#include <sstream>
#include "Expression.h"
#include "Value.h"

using namespace std;

class VariableDef
{
public:
	VariableDef(string name, int line, int column)
	{
		variable_name = name;
		is_array_def = false;
		initial_value = 0;
		this->line = line;
		this->column = column;
	}

	string ToString()
	{
		ostringstream out;

		out << "//Linea: " << line << ": Columna: " << column << endl;
		out << TypeToString(variable_type) << " " << variable_name;

		if (is_array_def)
			out << "[" << array_dimension << "]";

		if (initial_value != 0)
			out << " = " + initial_value->ToString();

		return out.str();
	}

	string variable_name;
	Type variable_type;
	bool is_array_def;
	Expression *initial_value;
	int array_dimension;
	int line, column;
};

typedef list<VariableDef *> VariableDefList;

#endif /* VARIABLE_H_ */
