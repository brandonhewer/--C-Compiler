%option reentrant
%option c++

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

int make_int(char *s);
void count(void);
void comment(void);
%}

%%
"/*"			{ comment(); }

"auto"			  { count(); return Keywords::AUTO; }
"break"			  { count(); return Keywords::BREAK; }
"continue"		{ count(); return Keywords::CONTINUE; }
"else"			  { count(); return Keywords::ELSE; }
"extern"		  { count(); return Keywords::EXTERN; }
"if"			    { count(); return Keywords::IF; }
"int"			    { count(); return Keywords::INT; }
"function"		{ count(); return Keywords::FUNCTION; }
"return"		  { count(); return Keywords::RETURN; }
"void"			  { count(); return Keywords::VOID; }
"while"			  { count(); return Keywords::WHILE; }

{L}({L}|{D})*		{ count(); yylval = yytext; return IDENTIFIER; }

{D}+{IS}?		      { count(); yylval = make_int(yytext); return CONSTANT; }
L?'(\\.|[^\\'])+'	{ count(); return CONSTANT; }

L?\"(\\.|[^\\"])*\"	{ count(); yylval = make_int(yytext); return STRING_LITERAL; }

"<="		{ count(); return Comparators::LESS_THAN_OR_EQUAL_TO; }
">="		{ count(); return Comparators::GREATER_THAN_OR_EQUAL_TO; }
"=="		{ count(); return Comparators::EQUALS; }
"!="		{ count(); return Comparators::DOES_NOT_EQUAL; }
"="			{ count(); return Operators::ASSIGNMENT; }
"!"			{ count(); return Operators::INVERSION; }
"-"			{ count(); return Operators::MINUS; }
"+"			{ count(); return Operators::PLUS; }
"*"			{ count(); return Operators::ASTERIX; }
"/"			{ count(); return Operators::DIVIDE; }
"%"			{ count(); return Operators::MODULO; }
"<"			{ count(); return Comparators::LESS_THAN; }
">"			{ count(); return Comparators::GREATER_THAN; }
"("			{ count(); return '('; }
")"			{ count(); return ')'; }
";"			{ count(); return ';'; }
"{"     { count(); return '{'; }
"}"     { count(); return '}'; }
","			{ count(); return ','; }
":"			{ count(); return ':'; }

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

int make_int(char *s) {
  return *s!='\'' ? atoi(s) : *(s+1);
}
