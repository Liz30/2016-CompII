#include <cstdio>
#include "arbol.h"

map<string, int> vars_int;

void CodeBlockST::execute(){
    list<Statement *>::iterator i = stList.begin();
    while ( i != stList.end() ){
        Statement *nst = *i;
        //Kind_ST g = nst->getKind();
        //printf("WHILE Code, TIPO: %d\n", g);
        nst->execute();
        i++;
    }
}

void BlockST::execute(){
    list<Statement *>::iterator bi = blList.begin();
    while ( bi != blList.end() ){
        Statement *nst = *bi;
        //Kind_ST g = nst->getKind();
        //printf("WHILE Text, TIPO: %d\n", g);
        nst->execute();
        bi++;
    }
}
