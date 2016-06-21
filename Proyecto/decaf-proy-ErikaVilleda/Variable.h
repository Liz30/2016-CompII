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
#include <iostream>
#include <map>
#include "Expression.h"
#include "Value.h"
#include "FieldMethodDef.h"


using namespace std;

extern map<string, ResultValue> vars;
extern stringstream mipsCode;

class VariableDef : public FieldMethodDef
{
public:
	VariableDef(string name, int line, int column) : FieldMethodDef(name)
	{
		is_array_def = false;
		initial_value = 0;
		this->line = line;
		this->column = column;
	}

	virtual string ToString()
	{
		ostringstream out;

		out << "//Linea: " << line << ": Columna: " << column << endl;
		out << TypeToString(variable_type) << " " << name;

		if (is_array_def)
			out << "[" << array_dimension << "]";

		if (initial_value != 0)
			out << " = " + initial_value->ToString();

		return out.str();
	}

	virtual MethodKind getKind() { return FIELD; }

	virtual void Execute() {
			if (!ExistVarGlobal(name)){
					ResultValue r;
					r.type = variable_type;
					if (initial_value!=0){
							r = initial_value->Evaluate();
							if (r.type != variable_type){
									cout << " ERROR en Variable: " << line << "," << column << ": No se puede convertir " << TypeToString(variable_type) << " a " << TypeToString(r.type) << endl;
									r.type = variable_type;
							}
					}
					vars[name] = r;
			}
			else
					cout << " ERROR en Variable: " << line << "," << column << ": " << name << " ya ha sido declarada. "<< endl;
	}

	virtual string GenerateCode(){
		stringstream varCode;
		string t = TypeToMips(variable_type);
		ResultValue r;
		r.type = variable_type;

		// VALIDAR: name no exista.
		varCode << name << ":	 " << t;

		if (initial_value!=0){
				r = initial_value->Evaluate();
				if (r.type != variable_type){
						cout << " ERROR en Variable: " << line << "," << column << ": No se puede convertir " << TypeToString(variable_type) << " a " << TypeToString(r.type) << endl;
						r.type = variable_type;
				}
				else{
						switch (r.type){
							case Int: varCode << "	" << r.value.int_value; break;
							case Boolean: varCode << "	" << r.value.bool_value; break;
							case String: varCode << "	" << r.value.string_value; break;
						}
				}
				varCode << endl;
		}
		else
			varCode << endl;

		vars[name] = r;
		return varCode.str();
	}

	Type variable_type;
	bool is_array_def;
	Expression *initial_value;
	int array_dimension;
	int line, column;
};

typedef list<VariableDef *> VariableDefList;

#endif /* VARIABLE_H_ */
