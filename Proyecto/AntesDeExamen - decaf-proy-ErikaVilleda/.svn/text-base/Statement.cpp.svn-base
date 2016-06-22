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

/*
 * ExecuteStatement
 */
void AssignmentStatement::ExecuteStatement()
{
	/* TODO: Implementar AssignmentStatement::ExecuteStatement() */
}

void MethodCallStatement::ExecuteStatement()
{
	/* TODO: Implementar MethodCallStatement::ExecuteStatement() */
}

void IfStatement::ExecuteStatement()
{
	/* TODO: Implementar IfStatement::ExecuteStatement() */
}

void WhileStatement::ExecuteStatement()
{
	/* TODO: Implementar WhileStatement::ExecuteStatement() */
}

void ForStatement::ExecuteStatement()
{
	/* TODO: Implementar ForStatement::ExecuteStatement() */
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
	/* TODO: Implementar BlockStatement::ExecuteStatement() */
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

