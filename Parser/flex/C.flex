%option c++

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include "Parser/Parser.h"
#include "Parser/Token.hpp"

#include <string>

using namespace Parser;

int make_int(char *s);
void count(void);
void comment(void);
%}

%%
"/*"			{ comment(); }

"auto"			  { count(); return AUTO; }
"break"			  { count(); return BREAK; }
"continue"		{ count(); return CONTINUE; }
"else"			  { count(); return ELSE; }
"extern"		  { count(); return EXTERN; }
"if"			    { count(); return IF; }
"int"			    { count(); return INT; }
"function"		{ count(); return FUNCTION; }
"return"		  { count(); return RETURN; }
"void"			  { count(); return VOID; }
"while"			  { count(); return WHILE; }

{L}({L}|{D})*		{ count(); yylval = yytext; return IDENTIFIER; }

{D}+{IS}?		      { count(); yylval = make_int(yytext); return CONSTANT; }
L?'(\\.|[^\\'])+'	{ count(); return CONSTANT; }

L?\"(\\.|[^\\"])*\"	{ count(); yylval = make_int(yytext); return STRING_LITERAL; }

"<="		{ count(); return LE_OP; }
">="		{ count(); return GE_OP; }
"=="		{ count(); return EQ_OP }
"!="		{ count(); return NE_OP; }
"="			{ count(); return '='; }
"!"			{ count(); return '!'; }
"-"			{ count(); return '-'; }
"+"			{ count(); return '+'; }
"*"			{ count(); return '*'; }
"/"			{ count(); return '/'; }
"%"			{ count(); return '%'; }
"<"			{ count(); return '<'; }
">"			{ count(); return '>'; }
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
