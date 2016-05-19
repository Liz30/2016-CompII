%include {
    #include <cstdlib>
    #include <iostream>
    #include <map>
    #include <list>
    #include <string>
    #include <sstream>
    #include "lexer_util.h"
    #include "ast.h"

    using namespace std;

    void reportError(const char *format, ...);
    extern int error;
    extern int line;

    extern map<string, int> vars;
    BlockStatement* code;
}

%token_type {TokenInfo *}
%default_type {int}

%type statement {Statement*}
%type statement_list {BlockStatement*}
%type text_block {Statement*}
%type else_block {BlockStatement*}

%type expr {Expr*}
%type term {Expr*}
%type factor {Expr*}
%type bool_expr {Expr*}

%syntax_error {
    string strErr = getTokenString(yymajor, TOKEN);
    reportError("Line %d: Syntax error. Unexpected %s\n", line, strErr.c_str());
}

%start_symbol sstart

sstart ::= input.

input ::= statement_list TK_EOF. {  }

statement_list(A) ::= statement_list(B) statement(C). {
                                                          //cout<<"ERIKA TYPE: "<<B->getSTR()<<"    "<<C->getSTR()<<endl;
                                                          if (B->getKind() == BLOCK_STATEMENT){
                                                              BlockStatement* bl = (BlockStatement*)B;
                                                              bl->stList.push_back(C);
                                                              A = bl;
                                                              code = bl;
                                                          }
                                                          else{
                                                              list<Statement*> l;
                                                              l.push_back(B);
                                                              l.push_back(C);

                                                              A = new BlockStatement(l);
                                                              code = new BlockStatement(l);
                                                          }
                                                          //cout << "CODE: "<<code->stList.size()<<endl;
                                                   }
statement_list ::= statement. { }


statement(A) ::= KW_PRINT expr(E) TK_SEMICOLON.      { A = new PrintStatement(E); }
statement(A) ::= KW_ASSIGN TK_ID(I) TK_EQUAL expr(E) TK_SEMICOLON. { A = new AssignStatement(I->strValue, E); freeTokenInfo(I); }
statement(A) ::= text_block(B). { A = B; }
statement(A) ::= KW_IF TK_LPAREN bool_expr(B) TK_RPAREN TK_LSET statement_list(C) TK_RSET else_block(D) . { A = new IfStatement(B, C->stList, D->stList); }
statement(A) ::= KW_WHILE TK_LPAREN bool_expr(B) TK_RPAREN TK_LSET statement_list(C) TK_RSET. { A = new WhileStatement(B, C->stList); }

text_block(A) ::= TK_TEXT(T). { A = new TextStatement(T->strValue); freeTokenInfo(T); }

bool_expr(R) ::= bool_expr(A) TK_LESS expr(B). { R = new LessExpr(A, B); }
bool_expr(R) ::= expr(B). { R = B;}

else_block(A) ::= KW_ELSE TK_LSET statement_list(B) TK_RSET. { A = B; }

expr(R) ::= expr(A) TK_ADD term(B). { R = new AddExpr(A,B); }
expr(R) ::= expr(A) TK_SUB term(B). { R = new SubExpr(A,B); }
expr(R) ::= term(A).                { R = A; }

term(R) ::= term(A) TK_MULT factor(B). { R = new MultExpr(A,B); }
term(R) ::= term(A) TK_DIV factor(B). { R = new DivExpr(A,B); }
term(R) ::= factor(A). { R = A; }

factor(R) ::= TK_LPAREN expr(A) TK_RPAREN.    { R = A; }
factor(R) ::= TK_NUM(N).	{ R = new NumExpr(N->intValue); freeTokenInfo(N); }
factor(R) ::= TK_ID(I).	{ R = new IdExpr(I->strValue); freeTokenInfo(I);}
