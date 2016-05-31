/*
 * Class.h
 *
 *  Created on: Mar 29, 2009
 *      Author: Ivan Deras
 */

#ifndef CLASS_H_
#define CLASS_H_

#include <string>
#include <sstream>
#include "Variable.h"
#include "MethodDef.h"
#include "Util.h"

using namespace std;

class ClassDef
{
	public:
		ClassDef()
		{
			field_def_list = 0;
			method_def_list = 0;
		}

		ClassDef(string name, VariableDefList *field_def_list, MethodDefList *method_def_list)
		{
			this->name = name;
			this->field_def_list = field_def_list;
			this->method_def_list = method_def_list;
		}

		~ClassDef()
		{
			if (field_def_list != 0) {
				FreeList(field_def_list);

				delete field_def_list;
			}

			if (method_def_list != 0) {
				FreeList(method_def_list);

				delete method_def_list;
			}
		}

		string ToString()
		{
			ostringstream out;

			out << "class " << name << "\n";
			out << "{" << "\n";

			if (field_def_list != 0)
				out << ListToString(field_def_list, ";\n", true) << "\n";

			if (method_def_list != 0)
				out << ListToString(method_def_list, "\n\n", true);

			out << "}" << endl;

			return out.str();
		}

		void AddFieldDef(VariableDef *field_def);
		void AddMethod(MethodDef *method_def);

		string name;
		VariableDefList *field_def_list;
		MethodDefList *method_def_list;
};

#endif /* CLASS_H_ */
