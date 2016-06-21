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

extern bool mainExist;

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

			if (field_def_list != 0)
				out << ListToString(field_def_list, ";\n", true) << "\n";

			if (method_def_list != 0)
				out << ListToString(method_def_list, "\n\n", true);

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

		void FillVarsMethods(){
			FieldMethodDefList::iterator it = field_method_def_list->begin();
			while(it!=field_method_def_list->end()){
					FieldMethodDef* n = *it;
					if (n->getKind()==METHOD){
						MethodDef* nuevo = (MethodDef*)n;
						if (nuevo->name.compare("main")==0){
								if (mainExist){
										cout << " ERROR en ClassDef: Metodo \'main\' ya existe." << endl;
								}
								else{
									mainExist = true;
									AddMethod(nuevo);
								}
						}
						else
								AddMethod(nuevo);
					}
					if (n->getKind()==FIELD){
						VariableDef* nuevo = (VariableDef*)n;
						AddFieldDef(nuevo);
					}
					it++;
			}
		}

		void Execute(){
				/*FieldMethodDefList::iterator it = field_method_def_list->begin();
				while(it!=field_method_def_list->end()){
						FieldMethodDef* n = *it;
						if (n->getKind()==METHOD){
							MethodDef* nuevo = (MethodDef*)n;
							AddMethod(nuevo);
							nuevo->Execute();
						}
						if (n->getKind()==FIELD){
							VariableDef* nuevo = (VariableDef*)n;
							AddFieldDef(nuevo);
							nuevo->Execute();
						}
						it++;
				}
				//cout <<endl<< " Variables Globales: "<<field_def_list->size()<<endl;
				//cout <<" Metodos: " << method_def_list->size()<<endl;
				//cout <<" Todos: "<<field_method_def_list->size();*/
				FillVarsMethods();
				if (field_def_list!=0){
						VariableDefList::iterator it = field_def_list->begin();
						while (it!=field_def_list->end()){
							VariableDef* n = *it;
							n->Execute();
							it++;
						}
				}
				if (method_def_list!=0){
						MethodDefList::iterator itm = method_def_list->begin();
					 	while (itm!=method_def_list->end()){
						 	MethodDef* n = *itm;
						 	n->Execute();
						 	itm++;
				 		}
				}
		}

		void generateCode(){
			 FillVarsMethods();

			 if (field_def_list!=0){
				 	 mipsCode << "	.data"<< endl;
					 VariableDefList::iterator it = field_def_list->begin();
					 while (it!=field_def_list->end()){
						 VariableDef* n = *it;
						 mipsCode << n->GenerateCode();
						 it++;
					 }
		 	 }

			 if (method_def_list!=0){
				 	 mipsCode << endl << "	.text" << endl;
					 MethodDefList::iterator itm = method_def_list->begin();
					 while (itm!=method_def_list->end()){
						 MethodDef* n = *itm;
						 mipsCode<<n->GenerateCode();
						 itm++;
					 }
		   }

			 cout << mipsCode.str() << endl;
		}

		void AddFieldDef(VariableDef *field_def){
				if (field_def_list == 0)
					field_def_list = new VariableDefList;

				field_def_list->push_back(field_def);
		}
		void AddMethod(MethodDef *method_def){
				if (method_def_list == 0)
					method_def_list = new MethodDefList;

				method_def_list->push_back(method_def);
		}

		string name;
		VariableDefList *field_def_list;
		MethodDefList *method_def_list;
		FieldMethodDefList *field_method_def_list;
};

#endif /* CLASS_H_ */
