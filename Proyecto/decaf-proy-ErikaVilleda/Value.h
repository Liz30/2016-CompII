/*
 * Value.h
 *
 *  Created on: Mar 27, 2009
 *      Author: ivan_deras
 */

#ifndef VALUE_H_
#define VALUE_H_

#include <string>
#include <list>

using namespace std;

typedef unsigned char byte;

/*
 * Tipos de datos soportados por Decaf
 */
enum Type {
	Int,
	Char,
	Boolean,
	String,
	Void
};

inline string TypeToString(Type type)
{
	switch (type)
	{
		case Int: return "int";
		case Char: return "char";
		case Boolean: return "boolean";
		case String: return "string";
		case Void: return "void";
	}

	return "None";
}

inline string TypeToMips(Type type)
{
	switch (type)
	{
		case Int: return ".word";
		case Char: return ".byte";
		case Boolean: return ".word";
		case String: return ".asciiz";
		//case Void: return "void";
	}

	return "None";
}

/*
 * Esta estructura representa el resultado de la evaluación de una Expresion.
 * El caso de string_value será utilizado para la proposicion print, la cual
 * permite un string como parametro,
 */
struct ResultValue
{
	Type type;
	bool isConstant;
	string place;
	string code;
	union {
		int int_value;
		bool bool_value;
		char *string_value;
	} value;
};

/*
 * Esta estructura representa una referencia a una variable.
 */
struct LValue
{
	Type type;
	byte *ptr;
};

#endif /* VALUE_H_ */
