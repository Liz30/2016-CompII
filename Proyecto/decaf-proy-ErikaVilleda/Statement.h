/*
 * Proposicion.h
 *
 *  Created on: Mar 27, 2009
 *      Author: Ivan Deras
 */

#ifndef PROPOSICION_H_
#define PROPOSICION_H_

#include <list>
#include <string>
#include <map>
#include "Value.h"
#include "Variable.h"
#include "Expression.h"

using namespace std;

enum StatementKind
{
	skAssignment,
	skMethodCall,
	skIf,
	skWhile,
	skFor,
	skReturn,
	skBreak,
	skContinue,
	skBlock
};

extern map<string, ResultValue> vars;
extern map<string, ResultValue> varsTemp;
extern map<string, ResultValue> methods;

class Statement
{
	public:
		Statement(int line = 0, int column = 0)
		{
			this->line = line;
			this->column = column;
		}

		virtual StatementKind GetKind() = 0;
		virtual void ExecuteStatement() = 0;
		virtual string ToString() = 0;

		int line, column;
};

class AssignmentStatement: public Statement
{
	public:
		AssignmentStatement(Expression *lvalue, Expression *expr, int line, int column): Statement(line, column)
		{
			this->lvalue = lvalue;
			this->expr = expr;
		}

		~AssignmentStatement()
		{
			if (lvalue != 0)
				delete lvalue;

			if (expr != 0)
				delete expr;
		}

		virtual StatementKind GetKind()
		{
			return skAssignment;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		Expression *lvalue;
		Expression *expr;
};

class MethodCallStatement: public Statement
{
	public:
		MethodCallStatement(string name, ExpressionList *arguments, int line, int column): Statement(line, column)
		{
			this->name = name;
			this->arguments = arguments;
		}

		~MethodCallStatement()
		{
			if (arguments != 0) {
				FreeList(arguments);
				delete arguments;
			}
		}

		virtual StatementKind GetKind()
		{
			return skMethodCall;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		string name;
		ExpressionList *arguments;
};

class IfStatement: public Statement
{
	public:
		IfStatement(Expression *condition, Statement *true_part, Statement *false_part, int line, int column): Statement(line, column)
		{
			this->condition = condition;
			this->true_part = true_part;
			this->false_part = false_part;
		}

		~IfStatement()
		{
			if (condition != 0)
				delete condition;

			if (true_part != 0)
				delete true_part;

			if (false_part != 0)
				delete false_part;
		}

		virtual StatementKind GetKind()
		{
			return skIf;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		Expression *condition;
		Statement *true_part;
		Statement *false_part;
};

class WhileStatement: public Statement
{
	public:
		WhileStatement(Expression *condition, Statement *loop_body, int line, int column): Statement(line, column)
		{
			this->condition = condition;
			this->loop_body = loop_body;
		}

		~WhileStatement()
		{
			if (condition != 0)
				delete condition;
			if (loop_body != 0)
				delete loop_body;
		}

		virtual StatementKind GetKind()
		{
			return skWhile;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		Expression *condition;
		Statement *loop_body;
};

class ForStatement: public Statement
{
	public:
		ForStatement(Statement *assignment_list1, Expression *condition, Statement *assignment_list2, Statement *loop_body, int line, int column): Statement(line, column)
		{
			this->assignment_list1 = assignment_list1;
			this->assignment_list2 = assignment_list2;
			this->condition = condition;
			this->loop_body = loop_body;
		}

		~ForStatement()
		{
			if (assignment_list1 != 0)
				delete assignment_list1;
			if (assignment_list2 != 0)
				delete assignment_list2;
			if (condition != 0)
				delete condition;
			if (loop_body != 0)
				delete loop_body;
		}

		virtual StatementKind GetKind()
		{
			return skFor;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		Statement *assignment_list1;
		Statement *assignment_list2;
		Expression *condition;
		Statement *loop_body;
};

class ReturnStatement: public Statement
{
	public:
		ReturnStatement(Expression *expr, int line, int column): Statement(line, column)
		{
			this->expr = expr;
		}

		~ReturnStatement()
		{
			if (expr != 0)
				delete expr;
		}

		virtual StatementKind GetKind()
		{
			return skReturn;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		Expression *expr;
};

class BreakStatement: public Statement
{
	public:
		BreakStatement(int line, int column): Statement(line, column)
		{
		}

		virtual StatementKind GetKind()
		{
			return skAssignment;
		}

		virtual void ExecuteStatement();
		virtual string ToString();
};

class ContinueStatement: public Statement
{
	public:
		ContinueStatement(int line, int column): Statement(line, column)
		{
		}

		virtual StatementKind GetKind()
		{
			return skContinue;
		}

		virtual void ExecuteStatement();
		virtual string ToString();
};

typedef list<Statement *> StatementList;

class BlockStatement: public Statement
{
	public:
		BlockStatement(int line, int column): Statement(line, column)
		{
			variable_def_list = 0;
			statement_list = 0;
		}

		BlockStatement(VariableDefList *variable_def_list, StatementList *statement_list)
		{
			this->variable_def_list = variable_def_list;
			this->statement_list = statement_list;
		}

		~BlockStatement()
		{
			if (variable_def_list != 0) {
				FreeList(variable_def_list);
				delete variable_def_list;
			}
			if (statement_list != 0) {
				FreeList(statement_list);
				delete statement_list;
			}
		}

		virtual StatementKind GetKind()
		{
			return skBlock;
		}

		virtual void ExecuteStatement();
		virtual string ToString();

		void AddVariableDef(VariableDef *variable_def)
		{
			if (variable_def_list == 0)
				variable_def_list = new VariableDefList;

			variable_def_list->push_back(variable_def);
		}

		void AddStatement(Statement *statement)
		{
			if (statement_list == 0)
				statement_list = new StatementList;

			statement_list->push_back(statement);
		}

		VariableDefList *variable_def_list;
		StatementList *statement_list;
};

#endif /* PROPOSICION_H_ */
