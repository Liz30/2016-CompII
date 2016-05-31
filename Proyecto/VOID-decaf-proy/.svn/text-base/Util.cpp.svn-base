/*
 * Util.cpp
 *
 *  Created on: Apr 2, 2009
 *      Author: Ivan Deras
 */

#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "Util.h"
#include "Value.h"
#include "Variable.h"
#include "Expression.h"
#include "Statement.h"
#include "MethodDef.h"
#include "ClassDef.h"
#include "decaf_tokens.h"

using namespace std;

#define BUFFER_SIZE	1024

ifstream in;
static bool eof = false;
int current_line = 1;
static int token_start = 0;
static int token_length = 0;
static int token_next_start = 0;
char buffer[BUFFER_SIZE];
char *ptr = NULL;
int buffer_length = 0;
int buffer_pos = 0;

int FillBuffer(void)
{
	if (in.eof()) {
		eof = true;
		return 1;
	}

	buffer_pos = 0;
	token_start = -1;
	token_next_start = 1;
	eof = false;

	in.read(buffer, BUFFER_SIZE);
	buffer_length = in.gcount();
	ptr = buffer;

	if (buffer_length != BUFFER_SIZE) {
		eof = true;
	}

	return 0;
}

/*--------------------------------------------------------------------
 * GetNextChar
 *
 * reads a character from input for flex
 *------------------------------------------------------------------*/
int GetNextChar(char *b, int maxBuffer)
{
	while (buffer_pos >= buffer_length) {
		int ret = FillBuffer();
		if (ret != 0) {
			return 0;
		}
	}

	b[0] = ptr[buffer_pos];
	buffer_pos++;

	if (b[0] == '\n') {
		current_line++;
		ptr = &ptr[buffer_pos];
		buffer_pos = 0;
	}

	return b[0] == 0 ? 0 : 1;
}

void BeginToken(char *t, YYLTYPE *yylloc)
{
	token_start = token_next_start;
	token_length = strlen(t);
	token_next_start = buffer_pos;

	/* Location for bison --------------------------------------------*/
	yylloc->first_line = current_line;
	yylloc->first_column = token_start;
	yylloc->last_line = current_line;
	yylloc->last_column = token_start + token_length - 1;
}

