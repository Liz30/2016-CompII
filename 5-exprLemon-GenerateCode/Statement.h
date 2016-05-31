#include <string>
#include <list>
#include <map>
#include <iostream>
#include "Expression.h"

using namespace std;

extern map<string, int> vars;

enum StatementKind{
  ASSIGN_ST,
  PRINT_ST,
  TEXT_ST
};

class Statement {
  public:
    virtual void Execute() = 0;
    virtual StatementKind getKind() = 0;
};

typedef list<Statement*> StatementList;

class AssignStatement: public Statement {
  public:
    AssignStatement(string id, Expression* expr){
        this->id = id;
        this->expr = expr;
    }

    void Execute() { vars[this->id] = expr->Evaluate(); }
    StatementKind getKind() { return ASSIGN_ST; }

    string id;
    Expression* expr;
};

class PrintStatement: public Statement {
  public:
    PrintStatement(ExpressionList* expr_list){ this->expr_list = expr_list; }

    void Execute();
    StatementKind getKind() { return PRINT_ST; }

    ExpressionList* expr_list;
};

class TextStatement: public Statement {
  public:
    TextStatement(string text) { this->text = text; }

    void Execute() { cout<<text; }
    StatementKind getKind() { return TEXT_ST; }

    string text;
};
