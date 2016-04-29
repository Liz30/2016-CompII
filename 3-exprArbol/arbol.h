#ifndef _AST_H_
#define _AST_H_

#include <string>
#include <list>
#include <map>

using namespace std;

extern map<string, int> vars_int;

class Expr{
    public:
        virtual int evaluate() = 0;
};

#endif
