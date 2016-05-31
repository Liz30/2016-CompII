#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
#include <map>
#include <list>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;
extern map<string, int> vars;

enum ExpressionKind{
  ADD_EXPR,
  SUB_EXPR,
  DIV_EXPR,
  MULT_EXPR,
  INT_EXPR,
  ID_EXPR
};

class Expression
{
  public:
    virtual ExpressionKind getKind() = 0;
    //virtual string ToString() = 0;
    virtual string getCode() = 0;
    virtual int Evaluate() = 0;
};

typedef list<Expression*> ExpressionList;

class BinaryExpression: public Expression {
  public:
    BinaryExpression(Expression* expr1, Expression* expr2){
      this->expr1 = expr1;
      this->expr2 = expr2;
    }
    Expression* expr1;
    Expression* expr2;
};

class AddExpression: public BinaryExpression {
  public:
    AddExpression(Expression* expr1, Expression* expr2): BinaryExpression(expr1, expr2){}

    ExpressionKind getKind() { return ADD_EXPR; }
    string getCode();
    int Evaluate() { return (expr1->Evaluate() + expr2->Evaluate());
    }
};

class SubExpression: public BinaryExpression {
  public:
    SubExpression(Expression* expr1, Expression* expr2): BinaryExpression(expr1, expr2) {}

    ExpressionKind getKind() { return SUB_EXPR; }
    string getCode();
    int Evaluate() { return (expr1->Evaluate() - expr2->Evaluate()); }
};

class MultExpression: public BinaryExpression {
  public:
    MultExpression(Expression* expr1, Expression* expr2): BinaryExpression(expr1, expr2) {}

    ExpressionKind getKind() { return MULT_EXPR; }
    string getCode();
    int Evaluate() { return (expr1->Evaluate() * expr2->Evaluate()); }
};

class DivExpression: public BinaryExpression {
  public:
    DivExpression(Expression* expr1, Expression* expr2): BinaryExpression(expr1, expr2) {}

    ExpressionKind getKind() { return DIV_EXPR; }
    string getCode();
    int Evaluate() { return (expr1->Evaluate() / expr2->Evaluate()); }
};

class IntExpression: public Expression {
  public:
    IntExpression(int value){ this->value = value; }

    ExpressionKind getKind() { return INT_EXPR; }
    string getCode();
    int Evaluate() { return value; }

    int value;
};

class IdExpression: public Expression {
  public:
    IdExpression(string id) { this->id = id;  }

    ExpressionKind getKind() { return ID_EXPR; }
    string getCode();
    int Evaluate() { return vars[id]; }

    string id;
};

#endif
