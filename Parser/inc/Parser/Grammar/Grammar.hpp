#ifndef __GRAMMAR_HPP_
#define __GRAMMAR_HPP_

#include <boost/spirit/home/x3.hpp>

#include "Parser/Grammar/Identifier.hpp"
#include "Parser/Grammar/Keywords.hpp"
#include "Parser/Grammar/Rules.hpp"
#include "Parser/Grammar/StringLiteral.hpp"
#include "Parser/Grammar/Symbols.hpp"

namespace Parser {
namespace Grammar {

namespace x3 = boost::spirit::x3;

// Rules
auto const primary_expression_def
= IDENTIFIER
| x3::int_
| STRING_LITERAL
| LEFT_PAREN >> expression >> RIGHT_PAREN
;

auto const function_application_def
= primary_expression >> argument_expression_lists
;

auto const postfix_expression_def
= function_application | primary_expression
;

auto const argument_expression_list_def
= assignment_expression % COMMA
;

auto const argument_expression_lists_def
= +(LEFT_PAREN >> argument_expression_list >> RIGHT_PAREN)
;

auto const unary_expression_def
= *unary_operator >> postfix_expression
;

auto const multiply_def
= unary_expression >> STAR >> multiplicative_expression
;

auto const divide_def
= unary_expression >> SLASH >> multiplicative_expression
;

auto const modulo_def
= unary_expression >> PERCENT >> multiplicative_expression
;

auto const multiplicative_expression_def
= multiply | divide | modulo | unary_expression
;

auto const addition_def
= multiplicative_expression >> PLUS >> additive_expression
;

auto const subtraction_def
= multiplicative_expression >> MINUS >> additive_expression
;

auto const additive_expression_def
= addition | subtraction | multiplicative_expression
;

auto const less_than_def
= additive_expression >> LT_OP >> relational_expression
;

auto const less_than_or_equal_to_def
= additive_expression >> LE_OP >> relational_expression
;

auto const greater_than_def
= additive_expression >> GT_OP >> relational_expression
;

auto const greater_than_or_equal_to_def
= additive_expression >> GE_OP >> relational_expression
;

auto const relational_expression_def
= less_than | less_than_or_equal_to | greater_than |
  greater_than_or_equal_to | additive_expression
;

auto const equality_check_def
= relational_expression >> EQ_OP >> equality_expression
;

auto const not_equal_def
= relational_expression >> NE_OP >> equality_expression
;

auto const equality_expression_def
= equality_check | not_equal | relational_expression
;

auto const assignment_def
= unary_expression >> ASSIGN >> assignment_expression
;

auto const assignment_expression_def
= assignment | equality_expression
;

auto const expression_def
= assignment_expression >> *(COMMA >> assignment_expression)
;

auto const init_declarator_list_def
= init_declarator >> *(COMMA >> init_declarator)
;

auto const variable_initializer_def
= declaration_specifiers >> init_declarator_list >> SEMICOLON
;

auto const declaration_def
= variable_initializer | function_definition
;

auto const declaration_specifier_def
= storage_class_specifier | type_specifier
;

auto const declaration_specifiers_def
= +declaration_specifier
;

auto const declaration_specifiers_or_none_def
= *declaration_specifier
;

auto const identifier_in_brackets_def
= IDENTIFIER
| LEFT_PAREN >> identifier_in_brackets >> RIGHT_PAREN
| x3::eps >> x3::attr(nullptr)
;

auto const init_declarator_def
= declarator >> -("=" >> assignment_expression)
;

auto const parameters_or_identifiers_def
= parameter_list | identifier_list
| x3::eps >> x3::attr(AST::Parameters())
;

auto const function_declarator_def
= identifier_in_brackets >>
  LEFT_PAREN >> parameters_or_identifiers >> RIGHT_PAREN
;

auto const declarator_def
= function_declarator | identifier_in_brackets
;

auto const parameter_list_def
= parameter_declaration % COMMA
;

auto const parameter_declaration_def
= declaration_specifiers >> identifier_in_brackets
| declaration_specifiers >> x3::attr(static_cast<std::string *>(nullptr));
;

auto const identifier_list_def
= IDENTIFIER % COMMA
;

auto const parameter_type_list
= parameter_list >> -COMMA
;

auto const parameter_type_list_brackets
= LEFT_PAREN >> parameter_type_list >> RIGHT_PAREN
;

auto const statement_def
= compound_statement
| expression_statement
| if_statement
| if_else_statement
| iteration_statement
| jump_statement
;

auto const compound_statement_def
= LEFT_BRACE >> *(declaration | statement) >> RIGHT_BRACE
;

auto const statement_list_def
= +statement
;

auto const expression_statement_def
= expression >> SEMICOLON
;

auto const if_statement_def
= IF >> LEFT_PAREN >> expression >> RIGHT_PAREN >> statement
;

auto const if_else_statement_def
= if_statement >> ELSE >> statement
;

auto const iteration_statement_def
= WHILE >> LEFT_PAREN >> expression >> RIGHT_PAREN >> statement
;

auto const return_statement_def
= RETURN >> expression >> SEMICOLON
| RETURN >> SEMICOLON >> x3::attr(AST::Expression());

auto const jump_statement_def
= (jump_keywords >> SEMICOLON) | return_statement
;

auto const function_definition_def
=  declaration_specifiers_or_none
>> function_declarator
>> compound_statement
;

auto const external_declaration_def
= function_definition
| declaration
;

// parser start symbol
auto const translation_unit_def
= *external_declaration
;

BOOST_SPIRIT_DEFINE(
  primary_expression,
  function_application,
  postfix_expression,
  argument_expression_list,
  argument_expression_lists,
  unary_expression,
  multiply,
  divide,
  modulo,
  multiplicative_expression,
  addition,
  subtraction,
  additive_expression,
  less_than,
  less_than_or_equal_to,
  greater_than,
  greater_than_or_equal_to,
  relational_expression,
  equality_check,
  not_equal,
  equality_expression,
  assignment,
  assignment_expression,
  expression,
  declaration_specifier,
  declaration_specifiers,
  declaration_specifiers_or_none,
  variable_initializer,
  declaration,
  identifier_in_brackets,
  init_declarator,
  init_declarator_list,
  parameters_or_identifiers,
  function_declarator,
  declarator,
  parameter_list,
  parameter_declaration,
  identifier_list,
  statement,
  compound_statement,
  statement_list,
  expression_statement,
  if_statement,
  if_else_statement,
  iteration_statement,
  return_statement,
  jump_statement,
  function_definition,
  external_declaration,
  translation_unit
)

}
}

#endif
