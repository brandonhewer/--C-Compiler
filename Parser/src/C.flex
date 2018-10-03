D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include "Parser/C.tab.h"
#include "Parser/Token.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace Parser;

Token make_int(char*);
void count(void);
void comment(void);
%}

%%
"/*"			{ comment(); }

"auto"			{ count(); return Keyword::AUTO; }
"break"			{ count(); return Keyword::BREAK; }
"continue"		{ count(); return Keyword::CONTINUE; }
"else"			{ count(); return Keyword::ELSE; }
"extern"		{ count(); return Keyword::EXTERN; }
"if"			{ count(); return Keyword::IF; }
"int"			{ count(); return Keyword::INT; }
"function"		{ count(); return Keyword::FUNCTION; }
"return"		{ count(); return Keyword::RETURN; }
"void"			{ count(); return Keyword::VOID; }
"while"			{ count(); return Keyword::WHILE; }

{L}({L}|{D})*		{ count(); return Identifier{yytext}; }

{D}+{IS}?		    { count(); return make_int(yytext); }
L?'(\\.|[^\\'])+'	{ count(); return make_int(yytext); }

L?\"(\\.|[^\\"])*\"	{ count(); return yytext; }

"<="		{ count(); return Comparators::LESS_THAN_OR_EQUAL_TO; }
">="		{ count(); return Comparators::GREATER_THAN_OR_EQUAL_TO; }
"=="		{ count(); return Comparators::EQUALS; }
"!="		{ count(); return Comparators::NOT_EQUAL; }
"<"			{ count(); return Comparators::LESS_THAN; }
">"			{ count(); return Comparators::GREATER_THAN; }
";"			{ count(); return Punctuation::SEMICOLON; }
"{"     	{ count(); return Punctuation::LEFT_PARENTHESES; }
"}"     	{ count(); return Punctuation::RIGHT_PARENTHESES; }
","			{ count(); return Punctuation::COMMA; }
":"			{ count(); return Punctuation::COLON; }
"("			{ count(); return Punctuation::LEFT_BRACKET; }
")"			{ count(); return Punctuation::RIGHT_BRACKET; }
"="			{ count(); return Operators::ASSIGNMENT; }
"!"			{ count(); return Operators::INVERSION; }
"-"			{ count(); return Operators::MINUS; }
"+"			{ count(); return Operators::PLUS; }
"*"			{ count(); return Operators::MULTIPLY; }
"/"			{ count(); return Operators::DIVIDE; }
"%"			{ count(); return Operators::MODULO; }

[ \t\v\n\f]		{ count(); }
.				{ /* ignore bad characters */ }

%%

int yywrap(void) {
	return(1);
}


void comment(void) {
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}


int column = 0;

void count() {
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}

Token make_int(char *s) {
  return *s!='\'' ? atoi(s) : *(s+1);
}
