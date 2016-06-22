/*
 * Expression.cpp
 *
 *  Created on: Mar 27, 2009
 *      Author: Ivan Deras
 */

#include <sstream>
#include <iostream>
#include "ClassDef.h"
#include "Expression.h"

using namespace std;

extern ClassDef *class_def;
extern map<string, ResultValue> vars;
extern map<string, ResultValue> varsTemp;
extern map<string, ResultValue> methods;

extern map<string, int>  tempAvailable;
extern map<string, int>  tempSAvailable;
extern map<string, int>  paramAvailable;

extern const char* regtemp[];
extern const char* regtempsS[];
extern const char* regParam[];
extern bool mainExist;

string newTemp(){
  for (int i = 0; i < 10; i++){
    if (tempAvailable.find(regtemp[i]) == tempAvailable.end()) {
        tempAvailable[regtemp[i]] = 0;
        return string(regtemp[i]);
    }
  }
  return string ("");
}

string newTempsS(){
  for (int i = 0; i < 10; i++){
    if (tempSAvailable.find(regtempsS[i]) == tempSAvailable.end()) {
        tempSAvailable[regtempsS[i]] = 0;
        return string(regtempsS[i]);
    }
  }
  return string ("");
}

string newParam(){
  for (int i = 0; i < 4; i++){
      if (paramAvailable.find(regParam[i]) == paramAvailable.end()) {
          paramAvailable[regParam[i]] = 0;
          return string(regParam[i]);
      }
  }
  return string ("");
}

void releaseTemp(string key){
    tempAvailable.erase(key);
}

void releaseTempS(string key){
    tempSAvailable.erase(key);
}

void releaseParam(string key){
    paramAvailable.erase(key);
}

bool ExistMethod(string key){
		map<string, ResultValue>::iterator it = methods.find(key);
		if ( it != methods.end())
				return true;
		return false;
}

void ShowTemp(){
		cout<<endl<<"TEMP......"<<endl;
		map<string, ResultValue>::iterator iv = varsTemp.begin();
		for (iv; iv!=varsTemp.end(); iv++){
				cout << "  Temp[" << iv->first << "] => Tipo: " << iv->second.type << " Valor: ";
				switch (iv->second.type){
					case Int: cout << iv->second.value.int_value << endl; break;
					case Boolean: cout << iv->second.value.bool_value << endl; break;
			 }
		}
}

bool ExistVarGlobal(string key){
	map<string, ResultValue>::iterator it = vars.find(key);
	if ( it != vars.end())
			return true;
	return false;
}

bool ExistVarTemp(string key){
	map<string, ResultValue>::iterator it = varsTemp.find(key);
	if ( it != varsTemp.end())
			return true;
	return false;
}

/*
 * GenerateCode()
*/

ResultValue BinaryExpression::GenerateCode(){
  stringstream code;
  ResultValue r;
  ResultValue expr1_r = expr1->GenerateCode();
  ResultValue expr2_r = expr2->GenerateCode();

  if (expr1_r.type == expr2_r.type) {
      r.type = expr1_r.type;

      switch (oper){
          case OpAdd:
                if (expr1_r.isConstant && expr2_r.isConstant){
                    r.value.int_value = expr1->Evaluate().value.int_value + expr2->Evaluate().value.int_value;
                    r.code = "";
                    r.isConstant = true;
                }
                else if (expr1_r.isConstant){
                    r.place = newTemp();
                    code << expr2_r.code << endl <<
                        "	addi " << r.place << ", " << expr2_r.place << ", " << expr1_r.value.int_value << endl;
                    releaseTemp(expr2_r.place);
                    r.code = code.str();
                    r.value.int_value = 0;
                    r.isConstant = false;
                }
                else if (expr2_r.isConstant) {
                      r.place = newTemp();
                      code << expr1_r.code <<
                            "	addi " << r.place << ", " << expr1_r.place << ", " << expr2_r.value.int_value << endl;
                      releaseTemp(expr1_r.place);
                      r.code = code.str();
                      r.value.int_value = 0;
                      r.isConstant = false;
                }
                else {
                    r.place = newTemp();
                    code << expr1_r.code << endl <<
                        expr2_r.code << endl <<
                        "	add " << r.place << ", " << expr1_r.place << ", " << expr2_r.place << endl;
                    r.code = code.str();
                    r.value.int_value = 0;
                    r.isConstant = false;
                    releaseTemp(expr1_r.place);
                    releaseTemp(expr2_r.place);
                }
                break;
        }
      }
  return r;
}

ResultValue UnaryExpression::GenerateCode(){
  ResultValue r;
  return r;
}

ResultValue LValueExpression::GenerateCode(){
  ResultValue r;
  stringstream code;
  r.place = newTemp();

  if (ExistVarGlobal(variable_name)){
    r.type = vars[variable_name].type;
    code << "	lw " << r.place << ", " << variable_name << endl;
  }
  else if (ExistVarTemp(variable_name)){
            r.type = varsTemp[variable_name].type;
            code << "	lw " << r.place << ", " << variable_name << endl;
  }
  else{
      cout << " ERROR en Expression GC("<<line<<","<<column<<"): Variable \'"<<variable_name<<"\' no ha sido declarada. "<<endl;
  }
  r.isConstant = false;
  r.code = code.str();

  return r;
}

ResultValue MethodCallExpression::GenerateCode(){
  ResultValue r;
  return r;
}

ResultValue ConstantExpression::GenerateCode(){
  ResultValue value;

  value.type = constant_type;
  value.value.int_value = constant_value.int_value;
  value.value.bool_value = constant_value.bool_value;
  value.value.string_value = constant_value.string_value;
  value.isConstant = true;
  value.code = "";
  value.place = "";

  return value;
}


/*
 * Evaluate()
 */
ResultValue BinaryExpression::Evaluate()
{
	ResultValue value;
	ResultValue r1 = expr1->Evaluate();
	ResultValue r2 = expr2->Evaluate();

	if (r1.type == r2.type){
				switch (oper){
					case OpAdd:	value.type = r1.type;
											value.value.int_value = r1.value.int_value + r2.value.int_value; break;
					case OpSub:	value.type = r1.type;
											value.value.int_value = r1.value.int_value - r2.value.int_value; break;
					case OpMul:	value.type = r1.type;
											value.value.int_value = r1.value.int_value * r2.value.int_value; break;
					case OpDiv:	value.type = r1.type;
											value.value.int_value = r1.value.int_value / r2.value.int_value; break;
					case OpMod:	value.type = r1.type;
											value.value.int_value = r1.value.int_value % r2.value.int_value; break;
					case OpOr:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value || r2.value.bool_value; break;
					case OpAnd:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value && r2.value.bool_value; break;
					case OpGT:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value > r2.value.bool_value; break;
					case OpLT:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value < r2.value.bool_value; break;
					case OpGTE:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value >= r2.value.bool_value; break;
					case OpLTE:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value <= r2.value.bool_value; break;
					case OpEq:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value == r2.value.bool_value; break;
					case OpNotEq:	value.type = Boolean;
											value.value.bool_value = r1.value.bool_value != r2.value.bool_value; break;
					case OpRShift:	value.type = r1.type;
											value.value.int_value = r1.value.int_value >> r2.value.int_value; break;
					case OpLShift:	value.type = r1.type;
											value.value.int_value = r1.value.int_value << r2.value.int_value; break;
					/*case OpRot:	value.type = r1.type;
											value.value.int_value = r1.value.int_value << r2.value.int_value; break;					*/
				}
	} else
			cout << " ERROR en Expression ("<<line<<","<<column<<"): No puede convertirse \'" << TypeToString(r2.type) << "\' a \'" << TypeToString(r1.type) << "\' " << endl;
	return value;
}

ResultValue UnaryExpression::Evaluate()
{
	ResultValue value;
	ResultValue r1 = expr->Evaluate();

	switch (oper){
		case OpNot: value.type = r1.type;
								value.value.bool_value = ! (r1.value.bool_value);
								break;
		case OpAdd: break;
		case OpSub: break;
	}

	return value;
}

ResultValue LValueExpression::Evaluate()
{
	ResultValue value;

	if (ExistVarGlobal(variable_name)){
		value = vars[variable_name];
	}
	else if (ExistVarTemp(variable_name)){
						value = varsTemp[variable_name];
	}
	else{
			cout << " ERROR en Expression ("<<line<<","<<column<<"): Variable \'"<<variable_name<<"\' no ha sido declarada. "<<endl;
	}

	return value;
}

ResultValue MethodCallExpression::Evaluate()
{
	ResultValue value;

	if (ExistMethod(method_name)){
			MethodDefList::iterator it = class_def->method_def_list->begin();
			while (it!=class_def->method_def_list->end()){
					MethodDef* current = *it;
					if (current->name.compare(method_name)==0){
							// asignar los parametros

							if (method_arguments!=0 || current->method_parameters!=0)
									if ( (method_arguments!=0 && current->method_parameters==0) ||
											 (method_arguments==0 && current->method_parameters!=0) ){
												 	cout << " ERROR en Expression ("<<line<<","<<column<<"): Cantidad de argumentos es incorrecto."<<endl;
									}
									else{
											if  (method_arguments->size()==current->method_parameters->size()){
													cout << "       WWWIIIII..."<<endl;
													ExpressionList::iterator iexp = method_arguments->begin();
													ParameterDefList::iterator ipar = current->method_parameters->begin();
													while (iexp!=method_arguments->end()){
															Expression* e = *iexp;
															ResultValue r = e->Evaluate();
															ParameterDef* p = *ipar;

															if (r.type == p->parameter_type){
																	//asignar
															}
															else
																	cout << " ERROR en Expression ("<<line<<","<<column<<"): Tipos no son iguales."<<endl;
															iexp++; ipar++;
													}
													ShowTemp();
											}
											else
													cout << " ERROR en Expression ("<<line<<","<<column<<"): Cantidad de argumentos es incorrecto."<<endl;
									}
							// execute body
					}
					it++;
			}

			value = methods[method_name];

	}
	else{
			cout << " ERROR en Expression ("<<line<<","<<column<<"): Metodo \'"<<method_name<<"\' no ha sido declarado. "<<endl;
	}

	return value;
}

ResultValue ConstantExpression::Evaluate()
{
	ResultValue value;

	value.type = constant_type;
	value.value.int_value = constant_value.int_value;
	value.value.bool_value = constant_value.bool_value;
	value.value.string_value = constant_value.string_value;
  value.isConstant = true;
  value.code = "";
  value.place = "";

	return value;
}


/*
 * ToString()
 */

string OperatorToString(ExpressionOperator oper)
{
	switch (oper)
	{
		case OpAdd: return "+";
		case OpSub: return "-";
		case OpMul: return "*";
		case OpDiv: return "/";
		case OpMod: return "%";
		case OpAnd: return "&&";
		case OpOr: return "||";
		case OpNot: return "!";
		case OpGT: return ">";
		case OpLT: return "<";
		case OpGTE: return ">=";
		case OpLTE: return "<=";
		case OpEq: return "==";
		case OpNotEq: return "!=";
		case OpRShift: return ">>";
		case OpLShift: return "<<";
		case OpRot: return "rot";
		default:
				return "Unknown";
	}
}

string BinaryExpression::ToString()
{
	ostringstream out;

	out << expr1->ToString() << " " << OperatorToString(oper) << " " << expr2->ToString();

	return out.str();
}

string UnaryExpression::ToString()
{
	ostringstream out;

	out << OperatorToString(oper) << expr->ToString();

	return out.str();
}

string LValueExpression::ToString()
{
	ostringstream out;

	out << this->variable_name;

	if (array_index != 0)
		out << "[" << array_index->ToString() << "]";

	return out.str();
}

string MethodCallExpression::ToString()
{
	ostringstream out;

	out << this->method_name << "(" << ListToString(method_arguments, ", ", false) << ")";

	return out.str();
}

string ConstantExpression::ToString()
{
	ostringstream out;

	switch (constant_type)
	{
		case Int: 		out << constant_value.int_value; break;
		case Boolean:	out << constant_value.bool_value; break;
		case String:	out << constant_value.string_value; break;
	}

	return out.str();
}
