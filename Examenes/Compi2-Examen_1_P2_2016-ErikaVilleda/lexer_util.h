#ifndef EXPR_LEXER_H
#define EXPR_LEXER_H
#include <string>
#include <sstream>

using namespace std;

struct TokenInfo {
    int tokenType;
    string strValue;
    int intValue;

    TokenInfo(int tokenType, string strValue) {
        this->tokenType = tokenType;
        this->strValue = strValue;
    }
};

template <typename T>
string convertToString(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

string getTokenString(int token, TokenInfo *info);
TokenInfo *allocTokenInfo(int tokenType, string strValue);
void freeTokenInfo(TokenInfo *ti);
void reportError(const char *format, ...);

#endif
