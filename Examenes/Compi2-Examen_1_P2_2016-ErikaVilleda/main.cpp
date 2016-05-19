#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <set>
#include "tokens.h"
#include "lexer_util.h"
#include "ast.h"

using namespace std;

extern BlockStatement* code;

int nextToken(struct TokenInfo *&p_info);

/* Parser related functions */
void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));
void Parse(void *yyp, int yymajor, TokenInfo *yyminor);

int error;

set<TokenInfo *> tiSet;

TokenInfo *allocTokenInfo(int tokenType, string strValue)
{
    TokenInfo *ti = new TokenInfo(tokenType, strValue);
    //printf("Alloc: %p\n", ti);
    if (ti != NULL) {
        tiSet.insert(ti);
    }

    return ti;
}

void freeTokenInfo(TokenInfo *ti)
{
    //printf("Free: %p\n", ti);
    if (tiSet.find(ti) != tiSet.end()) {
        tiSet.erase(ti);
        delete ti;
    } else {
        printf("Error trying to delete TokenInfo non existant");
    }
}

string getTokenString(int token, TokenInfo *info);

int main()
{
    void *parser = ParseAlloc(malloc);
    TokenInfo *ti;

    int token = nextToken(ti);
    while (token != TK_EOF) {
        Parse(parser, token, ti);
        token = nextToken(ti);
    }
    Parse(parser, TK_EOF, ti);
    ParseFree(parser, free);

    code->execute();

    set<TokenInfo *>::iterator it = tiSet.begin();

    while (it != tiSet.end()) {
        ti = *it;
        string text = getTokenString(ti->tokenType, ti);
        printf("Memory leak detected: %p %s\n", ti, text.c_str());
        it++;
    }

    if (tiSet.size() == 0) {
        cout << (char)0x1B << "[32;1mNo memory leaks detected" << (char)0x1B << "[0m" << endl;
    }

    return 0;
}

void reportError(const char *format, ...)
{
    va_list args;

    error++;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
