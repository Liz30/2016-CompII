/*
 * Expression.cpp
 *
 *  Created on: Mar 27, 2009
 *      Author: Ivan Deras
 */

#include <sstream>
#include "Expression.h"

using namespace std;

/*
 * Evaluate()
 */
ResultValue BinaryExpression::Evaluate()
{
	ResultValue value;

	/*TODO: Implementar BinaryExpression::Evaluate */

	return value;
}

ResultValue UnaryExpression::Evaluate()
{
	ResultValue value;

	/*TODO: Implementar UnaryExpression::Evaluate */

	return value;
}

ResultValue LValueExpression::Evaluate()
{
	ResultValue value;

	/*TODO: Implementar LValueExpression::Evaluate */

	return value;
}

ResultValue MethodCallExpression::Evaluate()
{
	ResultValue value;

	/*TODO: Implementar MethodCallExpression::Evaluate */

	return value;
}

ResultValue ConstantExpression::Evaluate()
{
	ResultValue value;

	/*TODO: Implementar ConstantExpression::Evaluate */

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

