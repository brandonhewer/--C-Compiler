%define api.value.type variant
%define api.token.constructor

%skeleton "lalr1.cc"

%code requires {
#include "Parser/ASTNode.hpp"

#include <unordered_map>

#define YYDEBUG 1

using namespace Parser;

std::unique_ptr<ASTNode> make_identifier(
    std::string const &s, std::unordered_map<std::string, Token> &symbols);
}

%param { std::unique_ptr<ASTNode> tree }
%param { std::unordered_map<std::string, Token> &symbols }

%token <std::string> IDENTIFIER;
%token <std::string> STRING_LITERAL;
%token <int> CONSTANT;

%token LE_OP GE_OP NE_OP EQ_OP;
%token EXTERN AUTO
%token INT VOID FUNCTION
%token APPLY LEAF
%token IF ELSE WHILE CONTINUE BREAK RETURN

%type <std::unique_ptr<ASTNode>> goal
                                 primary_expression 
                                 postfix_expression 
                                 argument_expression_list 
                                 unary_expression
                                 multiplicative_expression 
                                 additive_expression
                                 relational_expression 
                                 equality_expression
                                 assignment_expression 
                                 expression
                                 declaration
                                 declaration_specifiers 
                                 init_declarator_list
                                 init_declarator 
                                 storage_class_specifier
                                 type_specifier 
                                 declarator 
                                 direct_declarator 
                                 parameter_list 
                                 parameter_declaration
                                 identifier_list 
                                 abstract_declarator
                                 direct_abstract_declarator 
                                 statement
                                 compound_statement 
                                 declaration_list
                                 statement_list
                                 expression_statement
                                 selection_statement
                                 iteration_statement
                                 jump_statement
                                 translation_unit
                                 external_declaration
                                 function_definition;
%type <Token> unary_operator pointer;

%start goal
%%

goal    :  translation_unit { $$ = std::move($1); }
        ;

primary_expression
	: IDENTIFIER          { $$ = make_identifier($1, symbols); }
	| CONSTANT            { $$ = make_node($1); }
	| STRING_LITERAL      { $$ = make_node($1); }
	| '(' expression ')'	
      { 
        $$ = std::move($2); 
      }
	;

postfix_expression
	: primary_expression		{ $$ = std::move($1); }
	| postfix_expression '(' ')'	
      {
        $$ = std::move($1); 
      }
  | postfix_expression '(' argument_expression_list ')' 
      {
			  $$ = make_node(Operators::APPLY, std::move($1), std::move($3)); 
      }
	;

argument_expression_list
  : assignment_expression		{ $$ = std::move($1); }
  | argument_expression_list ',' assignment_expression 
      {
        $$ = make_node(MetaOperators::SEPARATE, std::move($1), std::move($3)); 
      }
  ;

unary_expression
  : postfix_expression		          { $$ = std::move($1); }
  | unary_operator unary_expression 
      { 
        $$ = make_node($1, std::move($2), nullptr); 
      }
  ;

unary_operator
  : '&'   { $$ = Operators::AMPERSAND; }
  | '*'   { $$ = Operators::MULTIPLY; }
  | '+'		{ $$ = Operators::PLUS; }
  | '-'		{ $$ = Operators::MINUS; }
  | '!'	  { $$ = Operators::INVERSION; }
  ;

multiplicative_expression
	: unary_expression		{ $$ = std::move($1); }
	| multiplicative_expression '*' unary_expression 
      {
        $$ = make_node(Operators::MULTIPLY, std::move($1), std::move($3)); 
      }
	| multiplicative_expression '/' unary_expression 
      {
        $$ = make_node(Operators::DIVIDE, std::move($1), std::move($3)); 
      }
	| multiplicative_expression '%' unary_expression 
      {
        $$ = make_node(Operators::MODULO, std::move($1), std::move($3)); 
      }
	;

additive_expression
	: multiplicative_expression		{ $$ = std::move($1); }
	| additive_expression '+' multiplicative_expression 
      {
        $$ = make_node(Operators::PLUS, std::move($1), std::move($3)); 
      }
	| additive_expression '-' multiplicative_expression 
      {
        $$ = make_node(Operators::MINUS, std::move($1), std::move($3)); 
      }
	;

relational_expression
	: additive_expression		{ $$ = std::move($1); }
	| relational_expression '<' additive_expression	
      {
        $$ = make_node(Comparators::LESS_THAN, std::move($1), std::move($3)); 
      }
	| relational_expression '>' additive_expression 
      {
        $$ = make_node(Comparators::GREATER_THAN, std::move($1), std::move($3)); 
      }
	| relational_expression LE_OP additive_expression 
      {
        $$ = make_node(Comparators::LESS_THAN_OR_EQUAL_TO, 
                       std::move($1), std::move($3)); 
      }
	| relational_expression GE_OP additive_expression 
      {
        $$ = make_node(Comparators::GREATER_THAN_OR_EQUAL_TO, 
                       std::move($1), std::move($3)); 
      }
	;

equality_expression
	: relational_expression		{ $$ = std::move($1); }
	| equality_expression '=' relational_expression 
      {
        $$ = make_node(Operators::ASSIGNMENT, std::move($1), std::move($3)); 
      }
	| equality_expression NE_OP relational_expression 
      {
        $$ = make_node(Comparators::NOT_EQUAL, std::move($1), std::move($3)); 
      }
	;

assignment_expression
	: equality_expression		{ $$ = std::move($1); }
	| unary_expression EQ_OP assignment_expression 
      {
        $$ = make_node(Comparators::EQUALS, std::move($1), std::move($3)); 
      }
	;

expression
	: assignment_expression		{ $$ = std::move($1); }
	| expression ',' assignment_expression 
      {
        $$ = make_node(MetaOperators::SEPARATE, std::move($1), std::move($3)); 
      }
	;

declaration
	: declaration_specifiers ';'  { $$ = std::move($1); }
	| function_definition			{ $$ = std::move($1); }
	| declaration_specifiers init_declarator_list ';'
      {
        $$ = make_node(MetaOperators::DECLARE, std::move($1), std::move($2)); 
      }
	;

declaration_specifiers
	: storage_class_specifier		{ $$ = std::move($1); }
	| storage_class_specifier declaration_specifiers 
      {
        $$ = make_node(MetaOperators::COMPOSE_TYPE_SPECIFIERS, 
                       std::move($1), std::move($2)); 
      }
	| type_specifier	        	{ $$ = std::move($1); }
	| type_specifier declaration_specifiers 
      { 
        $$ = make_node(MetaOperators::COMPOSE_TYPE_SPECIFIERS, 
                       std::move($1), std::move($2)); 
      }
	;

init_declarator_list
	: init_declarator		{ $$ = std::move($1); }
	| init_declarator_list ',' init_declarator 
      { 
        $$ = make_node(MetaOperators::SEPARATE, std::move($1), std::move($3)); 
      }
	;

init_declarator
	: declarator		{ $$ = std::move($1); }
	| declarator '=' assignment_expression 
      { 
        $$ = make_node(Operators::ASSIGNMENT, std::move($1), std::move($3)); 
      }
	;

storage_class_specifier
	: EXTERN	{ $$ = make_node(Keywords::EXTERN); }
	| AUTO		{ $$ = make_node(Keywords::AUTO); }
	;

type_specifier
	: VOID		  { $$ = make_node(Keywords::VOID); }
	| INT		    { $$ = make_node(Keywords::INT); }
	| FUNCTION	{ $$ = make_node(Keywords::FUNCTION); }
	;

declarator
	: pointer direct_declarator	
      { 
        $$ = make_node(MetaOperators::POINTS_TO, std::move($1), std::move($2)); 
      }
	| direct_declarator		{ $$ = std::move($1); }
	;

direct_declarator
	: IDENTIFIER		{ $$ = make_node($1); }
	| '(' declarator ')'	
      { 
        $$ = std::move($2); 
      }
  | direct_declarator '(' parameter_list ')' 
      { 
        $$ = make_node(MetaOperators::DECLARE_FUNCTION, 
                       std::move($1), std::move($3)); 
      }
	| direct_declarator '(' identifier_list ')' 
      { 
        $$ = make_node(MetaOperators::DECLARE_FUNCTION, 
                       std::move($1), std::move($3)); 
      }
	| direct_declarator '(' ')' 
      { 
        $$ = make_node(MetaOperators::DECLARE_FUNCTION, std::move($1), nullptr); 
      }
	;

pointer
	: '*'                   { $$ = Pointer{1}; }
	| '*' pointer           { $$ = Pointer{$2.depth}; }
	;

parameter_list
	: parameter_declaration		{ $$ = std::move($1); }
	| parameter_list ',' parameter_declaration 
      { 
        $$ = make_node(MetaOperators::SEPARATE, std::move($1), std::move($3)); 
      }
	;

parameter_declaration
	: declaration_specifiers declarator 
      { 
        $$ = make_node(MetaOperators::DECLARE, std::move($1), std::move($2)); 
      }
	| declaration_specifiers abstract_declarator 
      { 
        $$ = make_node(MetaOperators::DECLARE, std::move($1), std::move($2)); 
      }
	| declaration_specifiers	{ $$ = std::move($1); }
	;

identifier_list
	: IDENTIFIER    { $$ = make_node($1); }
	| identifier_list ',' IDENTIFIER 
      {
        $$ = make_node(MetaOperators::SEPARATE, std::move($1), make_node($3)); 
      }
	;

abstract_declarator
	: pointer		        { $$ = std::move($1); }
	| direct_abstract_declarator    { $$ = std::move($1); }
	| pointer direct_abstract_declarator 
      { 
        $$ = make_node(MetaOperators::DECLARE_ABSTRACT, make_node($1), std::move($2)); 
      }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { $$ = std::move($2); }
	| '(' ')'                     { $$ = nullptr; }
	| '(' parameter_list ')'      { $$ = std::move($2); }
	| direct_abstract_declarator '(' ')' 
      { 
        $$ = make_node(Operators::APPLY, std::move($1), nullptr); 
      }
	| direct_abstract_declarator '(' parameter_list ')' 
      { 
        $$ = make_node(Operators::APPLY, std::move($1), std::move($3)); 
      }
	;

statement
	: compound_statement		  { $$ = std::move($1); }
	| expression_statement		{ $$ = std::move($1); }
	| selection_statement		  { $$ = std::move($1); }
	| iteration_statement		  { $$ = std::move($1); }
	| jump_statement		      { $$ = std::move($1); }
	;

compound_statement
	: '{' '}'                       { $$ = nullptr; }
	| '{' statement_list '}'	      { $$ = std::move($2); }
	| '{' declaration_list '}'	    { $$ = std::move($2); }
	| '{' declaration_list statement_list '}' 
      { 
        $$ = make_node(MetaOperators::COMPOUND_STATEMENTS, 
                       std::move($2), std::move($3)); 
      }
	;

declaration_list
	: declaration			{ $$ = std::move($1); }
	| declaration_list declaration 
      { 
        $$ = make_node(MetaOperators::COMPOUND_STATEMENTS, 
                       std::move($1), std::move($2)); 
      }
	;

statement_list
	: statement			{ $$ = std::move($1); }
	| statement_list statement 	
      { 
        $$ = make_node(MetaOperators::COMPOUND_STATEMENTS, 
                       std::move($1), std::move($2)); 
      }
	;

expression_statement
	: ';'				        { $$ = nullptr; }
	| expression ';'		{ $$ = std::move($1); }
	;

selection_statement
	: IF '(' expression ')' statement 
      { 
        $$ = make_node(Keywords::IF, std::move($3), std::move($5)); 
      }
	| IF '(' expression ')' statement ELSE statement
      { 
        $$ = make_node(Keywords::IF, std::move($3), 
                       make_node(Keywords::ELSE, std::move($5), std::move($7))); 
      }
	;

iteration_statement
	: WHILE '(' expression ')' statement 
      { 
        $$ = make_node(Keywords::WHILE, std::move($3), std::move($5)); 
      }
	;

jump_statement
	: CONTINUE ';'          
      { 
        $$ = make_node(Keywords::CONTINUE, nullptr, nullptr); 
      }
	| BREAK ';'             
      { 
        $$ = make_node(Keywords::BREAK, nullptr, nullptr); 
      }
	| RETURN ';'	          
      { 
        $$ = make_node(Keywords::RETURN, nullptr, nullptr); 
      }
	| RETURN expression ';' 
      { 
        $$ = make_node(Keywords::RETURN, std::move($2), nullptr); 
      }
	;

translation_unit
	: external_declaration		{ $$ = std::move($1); }
	| translation_unit external_declaration 
      { 
        $$ = make_node(MetaOperators::ADD_TO_TRANSLATION_UNIT, 
                       std::move($1), std::move($2));
      }
	;

external_declaration
	: function_definition            { $$ = std::move($1); }
	| declaration                    { $$ = std::move($1); }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement 
      {
        $$ = make_node(MetaOperators::DEFINE_FUNCTION, 
                       make_node(MetaOperators::DEFINE_FUNCTION_HEADER, std::move($1), 
                                 make_node(MetaOperators::DEFINE_FUNCTION_CALL_INTERFACE, 
                                           std::move($2), std::move($3))), 
                       std::move($4)); 
      }
	| declaration_specifiers declarator compound_statement  
      {
        $$ = make_node(MetaOperators::DEFINE_FUNCTION, 
                       make_node(MetaOperators::DEFINE_FUNCTION_HEADER, 
                                 std::move($1), std::move($2)), 
                       std::move($3)); 
      }
	| declarator declaration_list compound_statement  
      {
        $$ = make_node(MetaOperators::DEFINE_FUNCTION, 
                       make_node(MetaOperators::DEFINE_FUNCTION_HEADER, 
                                 std::move($1), std::move($2)), 
                       std::move($3)); 
      }
	| declarator compound_statement 
      { 
        $$ = make_node(MetaOperators::DEFINE_FUNCTION, std::move($1), 
                       std::move($2)); 
      }
  ;
%%
#include <stdio.h>

extern char yytext[];
extern int column;

int yyerror(char *s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

Identifier const *
get_or_insert_symbol(std::string const &symbol,
                     std::unordered_map<std::string, Identifier> &symbols) {
  auto symbolIt = symbols.find(s);
  if (symbols.end() != symbolIt)
    return &symbolIt.second;
  return &(symbols[symbol] = Identifier{symbol});
}

std::unique_ptr<ASTNode>
make_identifier(std::string const &symbol,
                std::unordered_map<std::string, Token> &symbols) {
  return std::make_unique<ASTNode>(get_or_insert_symbol(symbol, symbols));
}



