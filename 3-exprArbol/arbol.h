#ifndef _AST_H_
#define _AST_H_

#include <string>
#include <cstdio>
#include <list>
#include <map>

using namespace std;

extern map<string, int> vars_int;

//  EXPRESION   --------------------------*/
/* --------------     CLASE BASE    -------------------------*/
class Expr{
    public:
        virtual int evaluate() = 0;
};

/* ------------------   TIPOS DE DATOS    ---------------------- */
class IntExpr: public Expr{
    public:
        IntExpr(int num){ this->num = num; }
        int evaluate() { return num; }
        int num;
};

class IdExpr: public Expr{
    public:
        IdExpr(string id) { this->id = id; }
        int evaluate() { return vars_int[id]; }
        string id;
};

/* TO DO evaluate devuelva cualquier tipo.
class TextExpr: public Expr{
    public:
        TextExpr(string mtext){ this->mtext=mtext; }
        int evaluate
}*/

/*  --------------     OPERACIONES BINARIAS  ------------------  */
class BinaryExpr: public Expr{
    public:
        BinaryExpr(Expr *expr1, Expr *expr2){
            this->expr1 = expr1;
            this->expr2 = expr2;
        }
        Expr *expr1;
        Expr *expr2;
};

class SumExpr: public BinaryExpr{
    public:
        SumExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2){}
        int evaluate(){
            int n1 = expr1 -> evaluate();
            int n2 = expr2 -> evaluate();
            return (n1+n2);
        }
};

class RestExpr: public BinaryExpr{
    public:
        RestExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2){}
        int evaluate(){
            int n1 = expr1 -> evaluate();
            int n2 = expr2 -> evaluate();
            return (n1-n2);
        }
};

class MultExpr: public BinaryExpr{
    public:
        MultExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2){}
        int evaluate(){
            int n1 = expr1 -> evaluate();
            int n2 = expr2 -> evaluate();
            return (n1*n2);
        }
};

class DivExpr: public BinaryExpr{
    public:
        DivExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2){}
        int evaluate(){
            int n1 = expr1 -> evaluate();
            int n2 = expr2 -> evaluate();
            return (n1/n2);
        }
};

//  STATEMENTS   --------------------------*/
enum Kind_ST{
    ASSIGN_ST,
    PRINT_ST,
    TEXTBLOCK_ST,
    CODEBLOCK_ST,
    BLOCK_ST
};
/*  ---------------   CLASE BASE    ------------------------ */
class Statement{
    public:
        virtual void execute() = 0;
        virtual Kind_ST getKind() = 0;
};

class BlockST: public Statement{
    public:
        BlockST(list<Statement *> blList){ this->blList=blList; }
        void execute();
        Kind_ST getKind() { return BLOCK_ST; }
        list<Statement *> blList;
};

class CodeBlockST: public Statement{
    public:
        CodeBlockST(list<Statement *> stList){ this->stList=stList; }
        void execute();
        Kind_ST getKind() { return CODEBLOCK_ST; }
        list<Statement *> stList;
};

class TextBlockST: public Statement {
    public:
        TextBlockST(char* mtext){ this->mtext=mtext; }
        void execute() { printf("%s\n", mtext); }
        Kind_ST getKind() { return TEXTBLOCK_ST; }
        char* mtext;
};

class AssignST: public Statement {
    public:
        AssignST(string id, Expr *expr){
            this->id = id;
            this->expr = expr;
        }
        void execute(){ vars_int[id] = expr->evaluate(); }
        Kind_ST getKind() { return ASSIGN_ST; }
        string id;
        Expr *expr;
};

class PrintST: public Statement {
    public:
        PrintST(Expr *expr){  this->expr = expr; }
        void execute() { printf("%d\n", expr->evaluate()); }
        Kind_ST getKind() { return PRINT_ST; }
        Expr *expr;
};

#endif
