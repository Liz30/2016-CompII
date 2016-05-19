#ifndef _AST_H_
#define _AST_H_

#include <string>
#include <list>
#include <map>

using namespace std;

extern map<string, int> vars;

class Declaration;

class Expr {
public:
    virtual int evaluate() = 0;
};

class BinaryExpr: public Expr {
public:
    BinaryExpr(Expr *expr1, Expr *expr2) {
        this->expr1 = expr1;
        this->expr2 = expr2;
    }

    Expr *expr1;
    Expr *expr2;
};

class AddExpr: public BinaryExpr {
public:
    AddExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}

    int evaluate();
};

class SubExpr: public BinaryExpr {
public:
    SubExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}

    int evaluate();
};

class MultExpr: public BinaryExpr {
public:
    MultExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}

    int evaluate();
};

class DivExpr: public BinaryExpr {
public:
    DivExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}

    int evaluate();
};

/* Added by Erika V. */
class LessExpr: public BinaryExpr {
public:
    LessExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}
    int evaluate();
};

/* -----------------*/

class NumExpr: public Expr {
public:
    NumExpr(int value) {
        this->value = value;
    }

    int evaluate() { return value; }

    int value;
};

class IdExpr: public Expr {
public:
    IdExpr(string id) { this->id = id; }
    int evaluate();

    string id;
};

enum StatementKind {
    BLOCK_STATEMENT,
    PRINT_STATEMENT,
    ASSIGN_STATEMENT,
    TEXT_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT
};

class Statement {
public:
    virtual void execute() = 0;
    virtual StatementKind getKind() = 0;
    virtual string getSTR() = 0;
};

class BlockStatement: public Statement {
public:
    BlockStatement(list<Statement *> stList) { this->stList = stList; }
    void execute();
    StatementKind getKind() { return BLOCK_STATEMENT; }
    string getSTR() { return "BlockStatement"; }

    list<Statement *> stList;
};

class PrintStatement: public Statement {
public:
    PrintStatement(Expr *expr) { this->expr = expr; }
    void execute();
    StatementKind getKind() { return PRINT_STATEMENT; }
    string getSTR() { return "PrintStatement"; }

    Expr *expr;
};

class AssignStatement: public Statement {
public:
    AssignStatement(string id, Expr *expr) {
        this->id = id;
        this->expr = expr;
    }
    void execute();
    StatementKind getKind() { return ASSIGN_STATEMENT; }
    string getSTR() { return "AssignStatement"; }

    string id;
    Expr *expr;
};

class TextStatement: public Statement {
public:
    TextStatement(string text){ this->text = text; }
    void execute();
    StatementKind getKind() { return TEXT_STATEMENT; }
    string getSTR() { return "TextStatement"; }

    string text;
};

class IfStatement: public Statement {
public:
    IfStatement(Expr* cond, list<Statement*> truecode, list<Statement*> falsecode){
        this->cond = cond;
        this->truecode = truecode;
        this->falsecode = falsecode;
    }
    void execute();
    StatementKind getKind() { return IF_STATEMENT; }
    string getSTR() { return "IfStatement"; }

    Expr* cond;
    list<Statement*> truecode;
    list<Statement*> falsecode;
};

class WhileStatement: public Statement {
public:
    WhileStatement(Expr* cond, list<Statement*> block){ this->cond = cond; this->block = block;}

    void execute();
    StatementKind getKind() {return WHILE_STATEMENT;}
    string getSTR() { return "WhileStatement"; }

    Expr* cond;
    list<Statement*> block;
};

#endif
