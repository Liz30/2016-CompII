#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "lexer_util.h"
#include "ast.h"

using namespace std;

map<string, int> vars;

#define IMPLEMENT_ARITHMETIC_EVALUATE(CLASS, OP)    \
    int CLASS::evaluate()                \
    {                                    \
        int value1 = expr1->evaluate();  \
        int value2 = expr2->evaluate();  \
                                         \
        return (value1 OP value2);       \
    }

IMPLEMENT_ARITHMETIC_EVALUATE(AddExpr, +)
IMPLEMENT_ARITHMETIC_EVALUATE(SubExpr, -)
IMPLEMENT_ARITHMETIC_EVALUATE(MultExpr, *)
IMPLEMENT_ARITHMETIC_EVALUATE(DivExpr, /)
IMPLEMENT_ARITHMETIC_EVALUATE(LessExpr, <)

int IdExpr::evaluate()
{
    //printf("IDEXPR\n");
    if (vars.find(id) == vars.end()) {
        reportError("Identifier '%s' has not been declared\n", id.c_str());
        exit(1);
    }

    return vars[id];
}

void BlockStatement::execute()
{
    list<Statement *>::iterator it = stList.begin();

    while (it != stList.end()) {
        Statement *st = *it;
        //printf("StKind: %s\n",st->getSTR().c_str());
        st->execute();
        it++;
    }
}

void PrintStatement::execute()
{
    int result = expr->evaluate();
    printf("%d", result);
}

void AssignStatement::execute()
{
    //printf("ERIKA. Size de vars: %d\n", vars.size());
    /*if (vars.find(id) == vars.end()) {
            printf("Identifier '%s' has not been declared\n", id.c_str());
            exit(1);
    }*/

    int result = expr->evaluate();
    vars[id] = result;
}

void TextStatement::execute()
{
    printf("%s", text.c_str());
}

void IfStatement::execute()
{
    if (cond->evaluate()) {
        cout << "TRUE " <<  endl;
        if (!truecode.empty()) {
            list<Statement *>::iterator it = truecode.begin();
            while (it != truecode.end()) {
                Statement *st = *it;
                //printf("StKind: %s\n",st->getSTR().c_str());
                st->execute();
                it++;
            }
            //truecode->execute();
        }
    }
    else{
        cout << "FALSE" <<  endl;
        if (!falsecode.empty()){
            list<Statement *>::iterator it = falsecode.begin();
            while (it != falsecode.end()) {
                Statement *st = *it;
                //printf("StKind: %s\n",st->getSTR().c_str());
                st->execute();
                it++;
            }
            //falsecode->execute();
        }
    }
}

void WhileStatement::execute()
{
    while (cond->evaluate()){
      list<Statement *>::iterator it = block.begin();
      while (it != block.end()) {
          Statement *st = *it;
          //printf("StKind: %s\n",st->getSTR().c_str());
          st->execute();
          it++;
      }
    }
}
