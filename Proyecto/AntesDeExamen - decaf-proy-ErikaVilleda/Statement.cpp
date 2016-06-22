/*
 * Statement.cpp
 *
 *  Created on: Mar 27, 2009
 *      Author: Ivan Deras
 */

#include "Variable.h"
#include "Expression.h"
#include "Statement.h"
#include "Util.h"

extern const char* regtemp[];
extern const char* regtempsS[];
extern const char* regParam[];

/*
 * ExecuteStatement
 */
void AssignmentStatement::ExecuteStatement()
{
		ResultValue lvalue_r = lvalue->Evaluate();
		ResultValue rvalue_r = expr->Evaluate();
		LValueExpression* n = (LValueExpression*)lvalue;

		if (!ExistVarGlobal(n->variable_name) && !ExistVarTemp(n->variable_name)){
					cout << "("<<line<<","<<column<<"): Variable \'" << n->variable_name << "\' no ha sido declarada."<<endl;
		}
		else if (lvalue_r.type == rvalue_r.type){
				if (ExistVarGlobal(n->variable_name)){
						vars[n->variable_name] = rvalue_r;
				}
				if (ExistVarTemp(n->variable_name)){
						varsTemp[n->variable_name] = rvalue_r;
				}
		}
		else
				cout << " ERROR en Statement ("<<line<<","<<column<<"): Variable \'"<< n->variable_name << "\' No se puede convertir \'" << TypeToString(rvalue_r.type) << "\' a \'" << TypeToString(lvalue_r.type) << "\'"<<endl;
}

void MethodCallStatement::ExecuteStatement()
{
	if (name=="print"){
			ExpressionList::iterator it = arguments->begin();
			while (it!=arguments->end()){
					Expression* n = *it;
					ResultValue nr = n->Evaluate();
					//Revisar si exite la variable para evitar
					// imprimir muchos errores
					switch (nr.type){
						case Int: cout << nr.value.int_value; break;
						case String: cout << nr.value.string_value; break;
						case Boolean: cout << nr.value.bool_value; break;
						default: cout << "("<<line<<","<<column<<"): Tipo de dato no reconocido." << endl;
					}
					it++;
			}
			cout << endl;
	}
	else
			cout << " Test MethodCallStatement: "<<name<<endl;
	// Valor de retorno lo tiene que guardar en methods[name]

}

void IfStatement::ExecuteStatement()
{
		ResultValue r = condition->Evaluate();

		if (TypeToString(r.type)!="None"){
				if (r.value.bool_value){
						if (true_part!=0)
								true_part->ExecuteStatement();
				}
				else{
						if (false_part!=0)
								false_part->ExecuteStatement();
				}
		}
		else
				cout << " ERROR en If ("<<line<<","<<column<<"): Condicion no pudo evaluarse."<<endl;
}

void WhileStatement::ExecuteStatement()
{
		ResultValue r = condition->Evaluate();

		if (TypeToString(r.type)!="None"){
			while (r.value.bool_value){
					loop_body->ExecuteStatement();
					r = condition->Evaluate();
			}
		}
		else
				cout << " ERROR en While ("<<line<<","<<column<<"): Condicion no pudo evaluarse."<<endl;
}

void ForStatement::ExecuteStatement()
{
		assignment_list1->ExecuteStatement();
		ResultValue r = condition->Evaluate();

		if (TypeToString(r.type)!="None"){
				while (r.value.bool_value){
						loop_body->ExecuteStatement();
						assignment_list2->ExecuteStatement();
						r = condition->Evaluate();
				}
		}
		else
				cout << " ERROR en For ("<<line<<","<<column<<"): Condicion no pudo evaluarse."<<endl;
}

void ReturnStatement::ExecuteStatement()
{
	/* TODO: Implementar ReturnStatement::ExecuteStatement() */
}

void BreakStatement::ExecuteStatement()
{
	/* TODO: Implementar BreakStatement::ExecuteStatement() */
}

void ContinueStatement::ExecuteStatement()
{
	/* TODO: Implementar ContinueStatement::ExecuteStatement() */
}

void BlockStatement::ExecuteStatement()
{
		if (variable_def_list!=0){
				VariableDefList::iterator itv = variable_def_list->begin();
				while (itv!=variable_def_list->end()){
					VariableDef* n = *itv;

					if (!ExistVarTemp(n->name) && !ExistVarGlobal(n->name)){
							ResultValue r;
							r.type = n->variable_type;
							if (n->initial_value!=0){
									r = n->initial_value->Evaluate();
									if (r.type != n->variable_type){
											cout << " ERROR en Statement (" << n->line << "," << n->column << "): No se puede convertir " << TypeToString(n->variable_type) << " a " << TypeToString(r.type) << endl;
											r.type = n->variable_type;
									}
							}
							varsTemp[n->name] = r;
							//cout << "  BlockST: " << n->name << "  Tipo: " << r.type << endl;
					}
					else
							cout << " ERROR en Statement (" << n->line << "," << n->column << "): Variable \'" << n->name << "\' ya ha sido declarada." << endl;
					itv++;
				}

	  }

		if (statement_list!=0){
				StatementList::iterator its = statement_list->begin();
				while (its!=statement_list->end()){
						Statement* n = *its;
						n->ExecuteStatement();
						//cout << n->GetKind()<<endl;
						its++;
				}
	  }

		// Release Temp //
		if (variable_def_list!=0){
				VariableDefList::iterator it = variable_def_list->begin();
				while (it!=variable_def_list->end()){
					VariableDef* n = *it;
					varsTemp.erase(n->name);
					it++;
				}
		}
}


/*
 * GenerateCode
 */

string AssignmentStatement::GenerateCode(){
	stringstream varCode;

	ResultValue lvalue_r = lvalue->GenerateCode();
	ResultValue rvalue_r = expr->GenerateCode();
	LValueExpression* n = (LValueExpression*)lvalue;
	cout << " 1: " << lvalue_r.code << "        2: " << rvalue_r.code << endl;
	if (!ExistVarGlobal(n->variable_name) && !ExistVarTemp(n->variable_name)){
				cout << "("<<line<<","<<column<<"): Variable \'" << n->variable_name << "\' no ha sido declarada."<<endl;
	}
	else if (lvalue_r.type == rvalue_r.type){
					if (ExistVarGlobal(n->variable_name)){
							if (rvalue_r.isConstant){
									string p = newTemp();
									varCode << rvalue_r.code;
									varCode << "	li " << p << ", " << rvalue_r.value.int_value << endl; // VALIDAR los demas tipos (bool, string)
									varCode << "	sw " << p << ", " << n->variable_name << endl;
									releaseTemp(p);
							}
							else {
									string p = newTemp();
									varCode << rvalue_r.code;
									varCode << "	sw " << rvalue_r.place << ", " << n->variable_name << endl;
									releaseTemp(p);
							}
					}
					if (ExistVarTemp(n->variable_name)){
							if (rvalue_r.isConstant)
									varCode << "	li " << varsTemp[n->variable_name].place << ", " << rvalue_r.value.int_value << endl;
							else
									varCode << "	move " << varsTemp[n->variable_name].place << ", " << rvalue_r.place << endl;
					}
			 }
			else
					cout << " ERROR en Statement ("<<line<<","<<column<<"): Variable \'"<< n->variable_name << "\' No se puede convertir \'" << TypeToString(rvalue_r.type) << "\' a \'" << TypeToString(lvalue_r.type) << "\'"<<endl;
	return varCode.str();
}

string MethodCallStatement::GenerateCode(){
	stringstream varCode;
	/*
		READ:
		li	$v0, 5			# load appropriate system call code into register $v0;
										# code for reading integer is 5
		syscall					# call operating system to perform operation
		sw	$v0, int_value # int_value declared in data section or temp var

	*/
	return varCode.str();
}

string IfStatement::GenerateCode(){
	stringstream varCode;
	/*ResultValue r = condition->GenerateCode();

	varCode << r.code;
	varCode << "	beq " << r.place << ", $zero, else";
	varCode << true_part->GenerateCode();
	varCode << "	j endif";
	varCode << "else: " << endl << false_part->GenerateCode();
	varCode << "endif:" << endl;*/
	return varCode.str();
}

string WhileStatement::GenerateCode(){
	stringstream varCode;
	return varCode.str();
}

string ForStatement::GenerateCode(){
	stringstream varCode;
	return varCode.str();
}

string ReturnStatement::GenerateCode(){
	stringstream varCode;
	return varCode.str();
}

string BreakStatement::GenerateCode(){
	stringstream varCode;
	return varCode.str();
}

string ContinueStatement::GenerateCode(){
	stringstream varCode;
	return varCode.str();
}

string BlockStatement::GenerateCode(){
	stringstream varCode;

			if (variable_def_list!=0){
					VariableDefList::iterator itv = variable_def_list->begin();
					varCode << "	addi $sp, $sp, -" << (variable_def_list->size()+1)*4 << endl;
					int i = 0;

					while (itv!=variable_def_list->end()){
						VariableDef* n = *itv;
						ResultValue r;
						r.place = newTempsS(); // revisar que no se pase del limite de registros
						varCode << "	sw " << r.place << ", " << i << "($sp)" << endl;
						i+=4;

						if (!ExistVarTemp(n->name) && !ExistVarGlobal(n->name)){
								r.type = n->variable_type;
								if (n->initial_value!=0){
										r = n->initial_value->Evaluate();
										if (r.type != n->variable_type){
												cout << " ERROR en Statement (" << n->line << "," << n->column << "): No se puede convertir " << TypeToString(n->variable_type) << " a " << TypeToString(r.type) << endl;
												r.type = n->variable_type;
										}
								}
								varsTemp[n->name] = r;								//cout << "  BlockST: " << n->name << "  Tipo: " << r.type << endl;
						}
						else
								cout << " ERROR en Statement (" << n->line << "," << n->column << "): Variable \'" << n->name << "\' ya ha sido declarada." << endl;
						itv++;
					}
					varCode << "	sw $ra, " << i << "($sp)" << endl;
			}

			if (statement_list!=0){
					StatementList::iterator its = statement_list->begin();
					while (its!=statement_list->end()){
							Statement* n = *its;
							varCode << n->GenerateCode();
							its++;
					}
			}

			// Release Temp //
			if (variable_def_list!=0){
					VariableDefList::iterator it = variable_def_list->begin();
					int i = 0;
					while (it!=variable_def_list->end()){
						VariableDef* n = *it;
						varCode << "	lw " << varsTemp[n->name].place << ", " << i << "($sp)" << endl;
						releaseTempS(varsTemp[n->name].place);	// Libero los registros S.
						varsTemp.erase(n->name);
						it++;
						i+=4;
					}
					varCode << "	lw $ra, " << i << "($sp)" << endl;
					varCode << "	addi $sp, $sp, " << i+4 << endl;
			}

			return varCode.str();
}

/*
 * ToString
 */
string AssignmentStatement::ToString()
{
	ostringstream out;

	out << "// Linea " << line << " Columna " << column << "\n";
	out << lvalue->ToString() << " = " << expr->ToString() << ";";

	return out.str();
}

string MethodCallStatement::ToString()
{
	return this->name + "(" + ListToString(arguments, ", ", false) + ");";
}

string IfStatement::ToString()
{
	ostringstream out;

	out << "if (" << condition->ToString() << ")" << endl;
	out << true_part->ToString() << endl;

	if (false_part != 0) {
		out << "else" << endl;
		out << false_part->ToString() << endl;
	}

	return out.str();
}

string WhileStatement::ToString()
{
	ostringstream out;

	out << "while (" << condition->ToString() << ")" << endl;
	out << "{" << loop_body->ToString() << endl << "}";

	return out.str();
}

string ForStatement::ToString()
{
	return "for () {}";
}

string ReturnStatement::ToString()
{
	return "return " + expr->ToString() + ";";
}

string BreakStatement::ToString()
{
	return "break;";
}

string ContinueStatement::ToString()
{
	return "continue;";
}

string BlockStatement::ToString()
{
	ostringstream out;

	out << "{" << endl;

	if (variable_def_list != 0)
		out << ListToString(variable_def_list, ";\n", true) << endl;

	if (statement_list != 0)
		out << ListToString(statement_list, "\n", true);

	out << "}";

	return out.str();
}
