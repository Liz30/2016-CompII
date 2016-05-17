/*
 * MethodDef.h
 *
 *  Created on: Mar 28, 2009
 *      Author: Ivan Deras
 */

#ifndef METHODDEF_H_
#define METHODDEF_H_

#include <list>
#include <sstream>
#include "Statement.h"
#include "Value.h"

using namespace std;

struct ParameterDef
{
		ParameterDef(string name, Type type)
		{
			parameter_name = name;
			parameter_type = type;
		}

		string ToString()
		{
			return TypeToString(parameter_type) + " " + parameter_name;
		}

		string parameter_name;
		Type parameter_type;
};

typedef list<ParameterDef *> ParameterDefList;

class MethodDef
{
	public:
		MethodDef(string name)
		{
			method_name = name;
		}

		~MethodDef()
		{
			if (method_parameters != 0) {
				ParameterDefList::iterator it = method_parameters->begin();

				while (it != method_parameters->end()) {
					ParameterDef *p = *it;
					delete p;

					it++;
				}

				method_parameters->clear();
				delete method_parameters;
			}

			if (method_body != 0)
				delete method_body;
		}

		string ToString()
		{
			ostringstream out;

			out << TypeToString(method_return_type) << " " << method_name << "(";
			if (method_parameters != 0)
				out << ListToString(method_parameters, ", ", false);
			out << ")" << endl;
			out << method_body->ToString() << endl;

			return out.str();
		}

		string method_name;
		Type method_return_type;
		ParameterDefList *method_parameters;
		Statement *method_body;
};

typedef list<MethodDef *> MethodDefList;

#endif /* METHODDEF_H_ */
