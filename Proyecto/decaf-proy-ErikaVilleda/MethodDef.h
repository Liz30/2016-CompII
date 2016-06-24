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
#include <iostream>
#include <map>
#include "Statement.h"
#include "Value.h"
#include "FieldMethodDef.h"

using namespace std;
extern bool globalError;
extern map<string, ResultValue> varsTemp;
extern map<string, ResultValue> methods;

extern map<string, int>  tempAvailable;
extern map<string, int>  tempSAvailable;
extern map<string, int>  paramAvailable;

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

		bool ExecuteSemantic(){
				if (!ExistVarTemp(parameter_name) && !ExistVarGlobal(parameter_name)){
						ResultValue r;
						r.type = parameter_type;
						varsTemp[parameter_name] = r;
						//cout << " Parametro: " << parameter_name << "  Tipo: " << r.type << endl;
				}
				else{
						cout <<" ERROR en ParameterDef: \'" << parameter_name << "\' Parametro ya declarado o Variable Global ya existe." << endl;
						return false;
				}
				return true;
		}

		string parameter_name;
		Type parameter_type;
};

typedef list<ParameterDef *> ParameterDefList;

class MethodDef : public FieldMethodDef
{
	public:
		MethodDef(string name) : FieldMethodDef(name)	{	}

		~MethodDef()
		{
			if (method_parameters != 0) {
				ParameterDefList::iterator it = method_parameters->begin();

				while (it != method_parameters->end()) {
					ParameterDef *p = *it;
					varsTemp.erase(p->parameter_name);
					delete p;

					it++;
				}

				//varsTemp.clear();
				method_parameters->clear();
				delete method_parameters;
			}

			if (method_body != 0)
				delete method_body;

			//methods.erase(name);
		}

		virtual string ToString()
		{
			ostringstream out;

			out << TypeToString(method_return_type) << " " << name << "(";
			if (method_parameters != 0)
				out << ListToString(method_parameters, ", ", false);
			out << ")" << endl;
			out << method_body->ToString() << endl;

			return out.str();
		}

		virtual MethodKind getKind() { return METHOD; }

		virtual void Execute() {
				if (!ExistMethod(name)){
							cout << "METHOD: " << name << endl;
							ResultValue r;
							r.type = method_return_type;
							methods[name] = r;

							if (method_parameters != 0){
									ParameterDefList::iterator it = method_parameters->begin();
									while (it!=method_parameters->end()){
											ParameterDef* n = *it;
											if (!ExistVarTemp(n->parameter_name) && !ExistVarGlobal(n->parameter_name) ){
													ResultValue r;
													r.type = n->parameter_type;
													varsTemp[n->parameter_name] = r;
													//cout << name << " Parametro: " << n->parameter_name << "  Tipo: " << r.type << endl;
											}
											else
													cout <<" ERROR en MethodDef: \'" << n->parameter_name << "\' Parametro ya declarado en " << name << " o Variable ya existe." << endl;
											it++;
									}
							}

							if (method_body != 0){
									method_body->ExecuteStatement();
							}
							else cout << " Statement 0"<<endl;

							if(method_parameters!=0){
									//cout << " Release ParameterDefList"<<endl;
									ParameterDefList::iterator it = method_parameters->begin();
									while (it!=method_parameters->end()){
											ParameterDef* n = *it;
											varsTemp.erase(n->parameter_name);
											it++;
									}
							}
//							cout << " Metodo: " << name << " Tipo: " << methods[name] << endl;
				}
				else
					cout << " ERROR en MethodDef: \'"<< name <<"\' ya existe"<<endl;
		}

		virtual bool ExecuteSemantic(){

				if (globalError)
						return false;

				if (ExistMethod(name)){	// Se tuvo que haber creaddo en ClassDef.h
							ResultValue r;
							r.type = method_return_type;
							methods[name] = r;

							if (method_parameters != 0){
									if (method_parameters->size() > 4){
										cout << " ERROR en MethodDef: Metodo \'" << name <<"\' con mas de 4 parametros." << endl;
										return false;
									}
									else{
										ParameterDefList::iterator it = method_parameters->begin();
										while (it!=method_parameters->end()){
												ParameterDef* n = *it;
												if (!n->ExecuteSemantic())
														return false;
												it++;
										}
									}
							}

							if (method_body != 0){
									if (!method_body->ExecuteSemantic())
											return false;
							}

							if(method_parameters!=0){
									ParameterDefList::iterator it = method_parameters->begin();
									while (it!=method_parameters->end()){
											ParameterDef* n = *it;
											varsTemp.erase(n->parameter_name);
											it++;
									}
							}
				}
				else{
					cout << " ERROR en MethodDef: \'"<< name <<"\' ya existe"<<endl;
					return false;
				}
				return true;
		}

		virtual string GenerateCode(){
				stringstream varCode;

				varCode << endl << name << ":" << endl;
				ResultValue r = methods[name];

				if (method_parameters != 0){
						ParameterDefList::iterator it = method_parameters->begin();
						while (it!=method_parameters->end()){
								ParameterDef* n = *it;
								varsTemp[n->parameter_name].place = newParam();
								varsTemp[n->parameter_name].type = n->parameter_type;
								it++;
						}
				}

				if (method_body != 0){
						varCode << method_body->GenerateCode();
				}

				if(method_parameters!=0){
						//cout << " Release ParameterDefList"<<endl;
						ParameterDefList::iterator it = method_parameters->begin();
						while (it!=method_parameters->end()){
								ParameterDef* n = *it;
								releaseParam(varsTemp[n->parameter_name].place);
								varsTemp.erase(n->parameter_name);
								it++;
						}
				}

				return varCode.str();
		}


		Type method_return_type;
		ParameterDefList *method_parameters;
		Statement *method_body;

};

typedef list<MethodDef *> MethodDefList;

#endif /* METHODDEF_H_ */
