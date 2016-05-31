/*
 * Class.h
 *
 *  Created on: Mar 29, 2009
 *      Author: Ivan Deras
 */

#ifndef FIELD_METHOD_DEF_H_
#define FIELD_METHOD_DEF_H_

#include <string>
#include <sstream>

using namespace std;

enum MethodKind{
  FIELD,
  METHOD
};

class FieldMethodDef
{
public:
	FieldMethodDef(string name){
      this->name = name;
  }

  virtual MethodKind getKind() = 0;
  virtual string ToString() = 0;

  string name;
};

typedef list<FieldMethodDef *> FieldMethodDefList;

#endif /* FIELD_METHOD_DEF_H_ */
