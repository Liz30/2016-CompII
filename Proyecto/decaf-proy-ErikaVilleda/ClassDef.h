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
#include <iostream>
#include "Variable.h"
#include "MethodDef.h"
#include "Util.h"
#include "TokenInfo.h"

using namespace std;

class ClassDef
{
	public:
		ClassDef()
		{
			field_def_list = 0;
			method_def_list = 0;
		}

		ClassDef(string name, FieldMethodDefList* field_method_def_list){
			this->name = name;
			this->field_method_def_list = field_method_def_list;
			this->field_def_list = 0;
			this->method_def_list = 0;
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

			if (field_method_def_list != 0) {
				FreeList(field_method_def_list);

				delete field_method_def_list;
			}
		}

		string ToString()
		{
			ostringstream out;
			string separator;

			out << "class " << name << "\n";
			out << "{" << "\n";

			/*if (field_def_list != 0)
				out << ListToString(field_def_list, ";\n", true) << "\n";

			if (method_def_list != 0)
				out << ListToString(method_def_list, "\n\n", true);*/

			if (field_method_def_list != 0){
					FieldMethodDefList::iterator it = field_method_def_list->begin();
					while(it!=field_method_def_list->end()){
						FieldMethodDef* n = *it;
						out << n->ToString();
						it++;

						if (it != field_method_def_list->end()){
							if (n->getKind()==FIELD)
										separator=";\n";
							if(n->getKind()==METHOD)
										separator="\n\n";
							out << separator;
						}
						else
							out << separator;
					}

			}

			//out << ListToString(field_method_def_list, ";\n", true);
			out << "}" << endl;
			return out.str();
		}

		void Execute(){
				FieldMethodDefList::iterator it = field_method_def_list->begin();
				while(it!=field_method_def_list->end()){
						FieldMethodDef* n = *it;
						//cout << " Tipo: " << n->getKind() << endl;
						n->Execute();
						it++;
				}
		}

		void AddFieldDef(VariableDef *field_def);
		void AddMethod(MethodDef *method_def);

		string name;
		VariableDefList *field_def_list;
		MethodDefList *method_def_list;
		FieldMethodDefList *field_method_def_list;
};

#endif /* CLASS_H_ */
