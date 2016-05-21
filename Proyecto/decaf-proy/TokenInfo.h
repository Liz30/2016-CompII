#ifndef TOKENINFO_H_
#define TOKENINFO_H_

#include "Value.h"
#include "Expression.h"

struct TokenInfo {
    Type tokenType;
    char* strValue;
    int intValue;
    ExpressionOperator	oper;

    TokenInfo(Type tokenType, char* strValue) {
        this->tokenType = tokenType;
        this->strValue = strValue;
    }
};

string getTokenString(int token, TokenInfo *info);
TokenInfo *allocTokenInfo(int tokenType, string strValue);
void freeTokenInfo(TokenInfo *ti);

#endif
