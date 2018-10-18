#ifndef __PRINTERS_H
#define __PRINTERS_H

#include "Parser/AST/ASTAdapted.hpp"

#include <boost/algorithm/string/join.hpp>

#include <algorithm>
#include <ostream>

namespace {

using namespace Parser::AST;

std::string identifier_to_string(std::string *identifier);
std::string expression_to_string(Expression const &);
std::string expressions_to_string(std::vector<Expression> const &);
std::string unary_expression_to_string(UnaryExpression const &);
std::string multiplication_to_string(Multiplication const &);
std::string division_to_string(Division const &);
std::string modulo_to_string(Modulo const &);
std::string
multiplicative_expression_to_string(MultiplicativeExpression const &);
std::string addition_to_string(Addition const &);
std::string subtraction_to_string(Subtraction const &);
std::string additive_expression_to_string(AdditiveExpression const &);
std::string less_than_to_string(LessThan const &);
std::string greater_than_to_string(GreaterThan const &);
std::string less_than_or_equal_to_string(LessThanOrEqualTo const &);
std::string greater_than_or_equal_to_string(GreaterThanOrEqualTo const &);
std::string relational_expression_to_string(RelationalExpression const &);
std::string equals_to_string(Equals const &);
std::string not_equal_to_string(NotEqual const &);
std::string equality_expression_to_string(EqualityExpression const &);
std::string assignment_to_string(Assignment const &);
std::string assignment_expression_to_string(AssignmentExpression const &);
std::string function_application_to_string(FunctionApplication const &);
std::string primary_expression_to_string(PrimaryExpression const &);

std::string declaration_specifier_to_string(DeclarationSpecifier const &);
std::string
declaration_specifiers_to_string(std::vector<DeclarationSpecifier> const &);
std::string parameter_declaration_to_string(ParameterDeclaration const &);
std::string parameter_declaration_to_string(
    x3::forward_ast<ParameterDeclaration> const &parameter_declaration);
std::string parameter_declarations_to_string(Parameters const &);
std::string parameter_lists_to_string(std::vector<Parameters> const &);
std::string identifiers_to_string(Identifiers const &);
std::string
parameters_or_identifiers_to_string(ParametersOrIdentifiers const &);
std::string function_declarator_to_string(FunctionDeclarator const &);
std::string declarator_to_string(Declarator const &);
std::string init_declarator_to_string(InitDeclarator const &);
std::string init_declarators_to_string(std::vector<InitDeclarator> const &);
std::string variable_initializer_to_string(VariableInitializer const &);
std::string declaration_or_statement_to_string(DeclarationOrStatement const &);
std::string declaration_to_string(Declaration const &);
std::string declarations_to_string(std::vector<Declaration> const &);
std::string if_to_string(If const &);
std::string if_else_to_string(IfElse const &);
std::string while_to_string(While const &);
std::string return_to_string(Return const &);
std::string jump_statement_to_string(JumpStatement const &);
std::string statement_to_string(Statement const &);
std::string
statements_to_string(std::vector<x3::forward_ast<Statement>> const &);
std::string compound_statement_to_string(CompoundStatement const &);
std::string function_definition_to_string(FunctionDefinition const &);
std::string external_declaration_to_string(ExternalDeclaration const &);
std::string translation_unit_to_string(TranslationUnit const &);

char unary_operator_to_character(UnaryOperators const &unary_operator) {
  switch (unary_operator) {
  case UnaryOperators::REFERENCE:
    return '&';
  case UnaryOperators::DEREFERENCE:
    return '*';
  case UnaryOperators::POSITIVE:
    return '+';
  case UnaryOperators::INVERSION:
    return '!';
  case UnaryOperators::NEGATIVE:
    return '-';
  }
}

std::string type_specifier_to_string(TypeSpecifier const &type_specifier) {
  switch (type_specifier) {
  case TypeSpecifier::FUNCTION:
    return "TYPE(function)";
  case TypeSpecifier::INT:
    return "TYPE(int)";
  case TypeSpecifier::VOID:
    return "TYPE(void)";
  }
}

std::string storage_class_specifier_to_string(
    StorageClassSpecifier const &storage_class_specifier) {
  switch (storage_class_specifier) {
  case StorageClassSpecifier::EXTERN:
    return "STORAGE_CLASS(extern)";
  case StorageClassSpecifier::AUTO:
    return "STORAGE_CLASS(auto)";
  }
}

std::string jump_keyword_to_string(JumpKeywords const &jump_keyword) {
  switch (jump_keyword) {
  case JumpKeywords::CONTINUE:
    return "JUMP_KEYWORD(continue)";
  case JumpKeywords::BREAK:
    return "JUMP_KEYWORD(break)";
  }
}

struct primary_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(std::string *identifier) const {
    return identifier_to_string(identifier);
  }

  std::string operator()(std::string const &literal) const {
    return "STRING_LITERAL(" + literal + ")";
  }

  std::string operator()(int constant) const {
    return "INTEGER_CONSTANT(" + std::to_string(constant) + ")";
  }

  std::string operator()(Expression const &expression) const {
    return expression_to_string(expression);
  }
} primary_expression_to_string_;

struct postfix_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(PrimaryExpression const &expression) const {
    return primary_expression_to_string(expression);
  }

  std::string operator()(FunctionApplication const &application) const {
    return function_application_to_string(application);
  }
} postfix_expression_to_string_;

struct multiplicative_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(UnaryExpression const &unary_expression) const {
    return unary_expression_to_string(unary_expression);
  }

  std::string operator()(Multiplication const &multiplication) const {
    return multiplication_to_string(multiplication);
  }

  std::string operator()(Division const &division) const {
    return division_to_string(division);
  }

  std::string operator()(Modulo const &modulo) const {
    return modulo_to_string(modulo);
  }
} multiplicative_expression_to_string_;

struct additive_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(MultiplicativeExpression const &expression) const {
    return multiplicative_expression_to_string(expression);
  }

  std::string operator()(Addition const &addition) const {
    return addition_to_string(addition);
  }

  std::string operator()(Subtraction const &subtraction) const {
    return subtraction_to_string(subtraction);
  }

} additive_expression_to_string_;

struct relational_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(AdditiveExpression const &expression) const {
    return additive_expression_to_string(expression);
  }

  std::string operator()(LessThan const &less_than) const {
    return less_than_to_string(less_than);
  }

  std::string operator()(GreaterThan const &greater_than) const {
    return greater_than_to_string(greater_than);
  }

  std::string operator()(LessThanOrEqualTo const &less_than_or_equal_to) const {
    return less_than_or_equal_to_string(less_than_or_equal_to);
  }

  std::string
  operator()(GreaterThanOrEqualTo const &greater_than_or_equal_to) const {
    return greater_than_or_equal_to_string(greater_than_or_equal_to);
  }

} relational_expression_to_string_;

struct equality_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(RelationalExpression const &expression) const {
    return relational_expression_to_string(expression);
  }

  std::string operator()(Equals const &equals) const {
    return equals_to_string(equals);
  }

  std::string operator()(NotEqual const &not_equal) const {
    return not_equal_to_string(not_equal);
  }

} equality_expression_to_string_;

struct assignment_expression_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(Assignment const &assignment) const {
    return assignment_to_string(assignment);
  }

  std::string operator()(EqualityExpression const &equality_expression) const {
    return equality_expression_to_string(equality_expression);
  }

} assignment_expression_to_string_;

struct declarator_to_string_ : public boost::static_visitor<std::string> {

  std::string operator()(std::string *identifier) {
    return identifier_to_string(identifier);
  }

  std::string operator()(FunctionDeclarator const &declarator) {
    return function_declarator_to_string(declarator);
  }

} declarator_to_string_;

struct declaration_specifier_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(TypeSpecifier const &type_specifier) const {
    return type_specifier_to_string(type_specifier);
  }

  std::string
  operator()(StorageClassSpecifier const &storage_class_specifier) const {
    return storage_class_specifier_to_string(storage_class_specifier);
  }

} declaration_specifier_to_string_;

struct parameters_or_identifiers_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(Parameters const &parameter_declarations) const {
    return parameter_declarations_to_string(parameter_declarations);
  }

  std::string operator()(Identifiers const &identifiers) const {
    return identifiers_to_string(identifiers);
  }

} parameters_or_identifiers_to_string_;

struct jump_statement_to_string_ : public boost::static_visitor<std::string> {

  std::string operator()(Return const &return_statement) const {
    return return_to_string(return_statement);
  };

  std::string operator()(JumpKeywords const &jump_keyword) const {
    return jump_keyword_to_string(jump_keyword);
  }

} jump_statement_to_string_;

struct statement_to_string_ : public boost::static_visitor<std::string> {

  std::string operator()(CompoundStatement const &compound_statement) const {
    return compound_statement_to_string(compound_statement);
  }

  std::string operator()(Expression const &expression) const {
    return expression_to_string(expression);
  }

  std::string operator()(If const &if_statement) const {
    return if_to_string(if_statement);
  }

  std::string operator()(IfElse const &if_else) const {
    return if_else_to_string(if_else);
  }

  std::string operator()(While const &while_statement) const {
    return while_to_string(while_statement);
  }

  std::string operator()(JumpStatement const &jump_statement) const {
    return jump_statement_to_string(jump_statement);
  }

} statement_to_string_;

struct declaration_to_string_ : public boost::static_visitor<std::string> {

  std::string operator()(FunctionDefinition const &function_definition) const {
    return function_definition_to_string(function_definition);
  }

  std::string
  operator()(VariableInitializer const &variable_initializer) const {
    return variable_initializer_to_string(variable_initializer);
  }

} declaration_to_string_;

struct declaration_or_statement_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(Declaration const &declaration) const {
    return declaration_to_string(declaration);
  }

  std::string operator()(Statement const &statement) const {
    return statement_to_string(statement);
  }

} declaration_or_statement_to_string_;

struct external_declaration_to_string_
    : public boost::static_visitor<std::string> {

  std::string operator()(FunctionDefinition const &function_definition) const {
    return function_definition_to_string(function_definition);
  }

  std::string operator()(Declaration const &declaration) const {
    return declaration_to_string(declaration);
  }

} external_declaration_to_string_;

std::string identifier_to_string(std::string *identifier) {
  if (nullptr == identifier)
    return "";
  return "IDENTIFIER(" + *identifier + ")";
}

std::string primary_expression_to_string(PrimaryExpression const &expression) {
  return boost::apply_visitor(primary_expression_to_string_, expression);
}

std::string
postfix_expression_to_string(PostfixExpression const &postfix_expression) {
  return boost::apply_visitor(postfix_expression_to_string_,
                              postfix_expression);
}

std::string unary_operator_to_string(UnaryOperators const &unary_operator) {
  std::string output = "UNARY_OPERATOR(";
  output += unary_operator_to_character(unary_operator);
  return output + ")";
}

std::string
unary_operators_to_string(std::vector<UnaryOperators> const &unary_operators) {
  if (unary_operators.empty())
    return "";
  else if (unary_operators.size() == 1)
    return unary_operator_to_string(unary_operators.front());

  std::string operator_string = "UNARY_OPERATORS(";
  for (auto &&unary_operator : unary_operators)
    operator_string += unary_operator_to_character(unary_operator);
  return operator_string + ")";
}

std::string
unary_expression_to_string(UnaryExpression const &unary_expression) {
  return unary_operators_to_string(unary_expression.operators) + " " +
         postfix_expression_to_string(unary_expression.expression);
}

std::string multiplication_to_string(Multiplication const &multiplication) {
  return unary_expression_to_string(multiplication.lhs) + " * " +
         multiplicative_expression_to_string(multiplication.rhs.get());
}

std::string division_to_string(Division const &division) {
  return unary_expression_to_string(division.lhs) + " / " +
         multiplicative_expression_to_string(division.rhs.get());
}

std::string modulo_to_string(Modulo const &modulo) {
  return unary_expression_to_string(modulo.lhs) + " % " +
         multiplicative_expression_to_string(modulo.rhs.get());
}

std::string multiplicative_expression_to_string(
    MultiplicativeExpression const &expression) {
  return boost::apply_visitor(multiplicative_expression_to_string_, expression);
}

std::string addition_to_string(Addition const &addition) {
  return multiplicative_expression_to_string(addition.lhs) + " + " +
         additive_expression_to_string(addition.rhs.get());
}

std::string subtraction_to_string(Subtraction const &subtraction) {
  return multiplicative_expression_to_string(subtraction.lhs) + " - " +
         additive_expression_to_string(subtraction.rhs.get());
}

std::string
additive_expression_to_string(AdditiveExpression const &additive_expression) {
  return boost::apply_visitor(additive_expression_to_string_,
                              additive_expression);
}

std::string less_than_to_string(LessThan const &less_than) {
  return additive_expression_to_string(less_than.lhs) + " < " +
         relational_expression_to_string(less_than.rhs.get());
}

std::string greater_than_to_string(GreaterThan const &greater_than) {
  return additive_expression_to_string(greater_than.lhs) + " > " +
         relational_expression_to_string(greater_than.rhs.get());
}

std::string
less_than_or_equal_to_string(LessThanOrEqualTo const &less_than_or_equal_to) {
  return additive_expression_to_string(less_than_or_equal_to.lhs) + " <= " +
         relational_expression_to_string(less_than_or_equal_to.rhs.get());
}

std::string greater_than_or_equal_to_string(
    GreaterThanOrEqualTo const &greater_than_or_equal_to) {
  return additive_expression_to_string(greater_than_or_equal_to.lhs) + " >= " +
         relational_expression_to_string(greater_than_or_equal_to.rhs.get());
}

std::string relational_expression_to_string(
    RelationalExpression const &relational_expression) {
  return boost::apply_visitor(relational_expression_to_string_,
                              relational_expression);
}

std::string equals_to_string(Equals const &equals) {
  return relational_expression_to_string(equals.lhs) +
         " == " + equality_expression_to_string(equals.rhs.get());
}

std::string not_equal_to_string(NotEqual const &not_equal) {
  return relational_expression_to_string(not_equal.lhs) +
         " != " + equality_expression_to_string(not_equal.rhs.get());
}

std::string assignment_to_string(Assignment const &assignment) {
  return unary_expression_to_string(assignment.lhs) + " = " +
         assignment_expression_to_string(assignment.rhs.get());
}

std::string assignment_expression_to_string(
    AssignmentExpression const &assignment_expression) {
  return boost::apply_visitor(assignment_expression_to_string_,
                              assignment_expression);
}

std::string
function_application_to_string(FunctionApplication const &application) {
  return primary_expression_to_string(application.identifier) + "(" +
         expressions_to_string(application.argument_lists) + ")";
}

std::string
equality_expression_to_string(EqualityExpression const &equality_expression) {
  return boost::apply_visitor(equality_expression_to_string_,
                              equality_expression);
}

std::string expression_to_string(Expression const &expression) {
  std::vector<std::string> assignments;
  assignments.reserve(expression.size());
  std::transform(expression.begin(), expression.end(),
                 std::back_inserter(assignments),
                 assignment_expression_to_string);
  return boost::algorithm::join(assignments, "\n");
}

std::string
expressions_to_string(std::vector<Expression> const &argument_lists) {
  std::vector<std::string> argument_list_strings;
  argument_list_strings.reserve(argument_lists.size());
  std::transform(argument_lists.begin(), argument_lists.end(),
                 std::back_inserter(argument_list_strings),
                 expression_to_string);
  return boost::algorithm::join(argument_list_strings, "\n");
}

std::string declaration_specifier_to_string(
    DeclarationSpecifier const &declaration_specifier) {
  return boost::apply_visitor(declaration_specifier_to_string_,
                              declaration_specifier);
}

std::string declaration_specifiers_to_string(
    std::vector<DeclarationSpecifier> const &specifiers) {
  std::vector<std::string> specifier_strings;
  specifier_strings.reserve(specifiers.size());
  std::transform(specifiers.begin(), specifiers.end(),
                 std::back_inserter(specifier_strings),
                 declaration_specifier_to_string);
  return boost::algorithm::join(specifier_strings, " ");
}

std::string parameter_declaration_to_string(
    ParameterDeclaration const &parameter_declaration) {
  auto const prefix =
      declaration_specifiers_to_string(parameter_declaration.specifiers);
  auto const suffix = identifier_to_string(parameter_declaration.identifier);

  if (suffix.empty())
    return prefix;
  else if (prefix.empty())
    return suffix;
  return prefix + " " + suffix;
}

std::string parameter_declaration_to_string_forward(
    x3::forward_ast<ParameterDeclaration> const &parameter_declaration) {
  return parameter_declaration_to_string(parameter_declaration.get());
}

std::string
parameter_declarations_to_string(Parameters const &parameter_declarations) {
  std::vector<std::string> declaration_strings;
  declaration_strings.reserve(parameter_declarations.size());
  std::transform(parameter_declarations.begin(), parameter_declarations.end(),
                 std::back_inserter(declaration_strings),
                 parameter_declaration_to_string_forward);
  return "(" + boost::algorithm::join(declaration_strings, ",") + ")";
}

std::string parameter_lists_to_string(
    std::vector<Parameters> const &parameter_declarations) {
  std::vector<std::string> list_strings;
  list_strings.reserve(parameter_declarations.size());
  std::transform(parameter_declarations.begin(), parameter_declarations.end(),
                 std::back_inserter(list_strings),
                 parameter_declarations_to_string);
  return boost::algorithm::join(list_strings, "\n");
}

std::string identifiers_to_string(Identifiers const &identifiers) {
  std::vector<std::string> identifier_strings;
  identifier_strings.reserve(identifiers.size());
  std::transform(identifiers.begin(), identifiers.end(),
                 std::back_inserter(identifier_strings), identifier_to_string);
  return boost::algorithm::join(identifier_strings, ", ");
}

std::string parameters_or_identifiers_to_string(
    ParametersOrIdentifiers const &parameters_or_identifiers) {
  return boost::apply_visitor(parameters_or_identifiers_to_string_,
                              parameters_or_identifiers);
}

std::string
function_declarator_to_string(FunctionDeclarator const &function_declarator) {
  auto const prefix = identifier_to_string(function_declarator.identifier);
  auto const suffix =
      parameters_or_identifiers_to_string(function_declarator.parameters);

  if (suffix.empty())
    return prefix;
  else if (prefix.empty())
    return suffix;
  return prefix + " " + suffix;
}

std::string declarator_to_string(Declarator const &declarator) {
  return boost::apply_visitor(declarator_to_string_, declarator);
}

std::string init_declarator_to_string(InitDeclarator const &init_declarator) {
  std::string prefix = declarator_to_string(init_declarator.declarator);

  if (init_declarator.assignment)
    return prefix + " = " +
           assignment_expression_to_string(*init_declarator.assignment);
  return prefix;
}

std::string init_declarators_to_string(
    std::vector<InitDeclarator> const &init_declarators) {
  std::vector<std::string> declarator_strings;
  declarator_strings.reserve(init_declarators.size());
  std::transform(init_declarators.begin(), init_declarators.end(),
                 std::back_inserter(declarator_strings),
                 init_declarator_to_string);
  return boost::algorithm::join(declarator_strings, ",");
}

std::string variable_initializer_to_string(
    VariableInitializer const &variable_initializer) {
  return declaration_specifiers_to_string(variable_initializer.specifiers) +
         " " + init_declarators_to_string(variable_initializer.declarators);
}

std::string declaration_or_statement_to_string(
    DeclarationOrStatement const &declaration_or_statement) {
  return boost::apply_visitor(declaration_or_statement_to_string_,
                              declaration_or_statement);
}

std::string declaration_to_string(Declaration const &declaration) {
  return boost::apply_visitor(declaration_to_string_, declaration);
}

std::string
declarations_to_string(std::vector<Declaration> const &declarations) {
  std::vector<std::string> declaration_strings;
  declaration_strings.reserve(declarations.size());
  std::transform(declarations.begin(), declarations.end(),
                 std::back_inserter(declaration_strings),
                 declaration_to_string);
  return boost::algorithm::join(declaration_strings, ",");
}

std::string if_to_string(If const &if_statement) {
  return "IF(" + expression_to_string(if_statement.condition) + ")(\n" +
         statement_to_string(if_statement.body.get()) + "\n)";
}

std::string if_else_to_string(IfElse const &if_else) {
  return if_to_string(if_else.if_statement) + " ELSE(\n" +
         statement_to_string(if_else.else_body.get()) + "\n)";
}

std::string while_to_string(While const &while_statement) {
  return "WHILE(\n" + expression_to_string(while_statement.condition) + ")(\n" +
         statement_to_string(while_statement.body) + "\n)";
}

std::string return_to_string(Return const &return_statement) {
  if (!return_statement.expression.empty())
    return "RETURN(\n" + expression_to_string(return_statement.expression) +
           "\n)";
  return "RETURN";
}

std::string jump_statement_to_string(JumpStatement const &jump_statement) {
  return boost::apply_visitor(jump_statement_to_string_, jump_statement);
}

std::string statement_to_string(Statement const &statement) {
  return boost::apply_visitor(statement_to_string_, statement);
}

std::string
statement_to_string_forward(x3::forward_ast<Statement> const &statement) {
  return statement_to_string(statement.get());
}

std::string statements_to_string(
    std::vector<x3::forward_ast<Statement>> const &statements) {
  std::vector<std::string> statement_strings;
  statement_strings.reserve(statements.size());
  std::transform(statements.begin(), statements.end(),
                 std::back_inserter(statement_strings),
                 statement_to_string_forward);
  return boost::algorithm::join(statement_strings, "\n");
}

std::string
compound_statement_to_string(CompoundStatement const &compound_statement) {
  std::vector<std::string> strs;
  strs.reserve(compound_statement.size());
  for (auto &&statement : compound_statement)
    strs.emplace_back(declaration_or_statement_to_string(statement));
  return boost::algorithm::join(strs, "\n");
}

std::string function_definition_header_to_string(
    FunctionDeclarator const &declarator,
    std::vector<DeclarationSpecifier> const &specifiers) {
  auto const prefix = "FUNCTION " + identifier_to_string(declarator.identifier);
  auto const return_type = declaration_specifiers_to_string(specifiers);
  auto const parameters =
      parameters_or_identifiers_to_string(declarator.parameters);
  return prefix + " :: [" + parameters + " => " + return_type + "]";
}

std::string
function_definition_to_string(FunctionDefinition const &function_definition) {
  return function_definition_header_to_string(function_definition.declarator,
                                              function_definition.specifiers) +
         " {\n" + compound_statement_to_string(function_definition.body) +
         "\n}";
}

std::string external_declaration_to_string(
    ExternalDeclaration const &external_declaration) {
  return boost::apply_visitor(external_declaration_to_string_,
                              external_declaration);
}

std::string
translation_unit_to_string(TranslationUnit const &translation_unit) {
  std::vector<std::string> external_strings;
  external_strings.reserve(translation_unit.size());
  std::transform(translation_unit.begin(), translation_unit.end(),
                 std::back_inserter(external_strings),
                 external_declaration_to_string);
  return boost::algorithm::join(external_strings, "\n\n");
}

} // namespace

namespace Parser {
namespace AST {

std::ostream &operator<<(std::ostream &output_stream,
                         UnaryOperators const &unary_operator) {
  output_stream << unary_operator_to_string(unary_operator);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         TypeSpecifier const &type_specifier) {
  output_stream << type_specifier_to_string(type_specifier);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         StorageClassSpecifier const &storage_class_specifier) {
  output_stream << storage_class_specifier_to_string(storage_class_specifier);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         PostfixExpression const &postfix_expression) {
  output_stream << postfix_expression_to_string(postfix_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         PrimaryExpression const &primary_expression) {
  output_stream << primary_expression_to_string(primary_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         UnaryExpression const &unary_expression) {
  output_stream << unary_expression_to_string(unary_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Multiplication const &multiplication) {
  output_stream << multiplication_to_string(multiplication);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Division const &division) {
  output_stream << division_to_string(division);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream, Modulo const &modulo) {
  output_stream << modulo_to_string(modulo);
  return output_stream;
}

std::ostream &
operator<<(std::ostream &output_stream,
           MultiplicativeExpression const &multiplicative_expression) {
  output_stream << multiplicative_expression_to_string(
      multiplicative_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Addition const &addition) {
  output_stream << addition_to_string(addition);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Subtraction const &subtraction) {
  output_stream << subtraction_to_string(subtraction);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         AdditiveExpression const &additive_expression) {
  output_stream << additive_expression_to_string(additive_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream, Equals const &equals) {
  output_stream << equals_to_string(equals);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NotEqual const &not_equal) {
  output_stream << not_equal_to_string(not_equal);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         EqualityExpression const &equality_expression) {
  output_stream << equality_expression_to_string(equality_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Assignment const &assignment) {
  output_stream << assignment_to_string(assignment);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         AssignmentExpression const &assignment_expression) {
  output_stream << assignment_expression_to_string(assignment_expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Expression const &expression) {
  output_stream << expression_to_string(expression);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         DeclarationSpecifier const &specifier) {
  output_stream << declaration_specifier_to_string(specifier);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         ParameterDeclaration const &parameter_declaration) {
  output_stream << parameter_declaration_to_string(parameter_declaration);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Parameters const &parameters) {
  output_stream << parameter_declarations_to_string(parameters);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Identifiers const &identifiers) {
  output_stream << identifiers_to_string(identifiers);
  return output_stream;
}

std::ostream &
operator<<(std::ostream &output_stream,
           ParametersOrIdentifiers const &parameters_or_identifiers) {
  output_stream << parameters_or_identifiers_to_string(
      parameters_or_identifiers);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         InitDeclarator const &init_declarator) {
  output_stream << init_declarator_to_string(init_declarator);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Declaration const &declaration) {
  output_stream << declaration_to_string(declaration);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream, If const &if_statement) {
  output_stream << if_to_string(if_statement);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream, IfElse const &if_else) {
  output_stream << if_else_to_string(if_else);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         While const &while_statement) {
  output_stream << while_to_string(while_statement);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         JumpKeywords const &jump_keyword) {
  output_stream << jump_keyword_to_string(jump_keyword);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Return const &return_statement) {
  output_stream << return_to_string(return_statement);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         JumpStatement const &jump_statement) {
  output_stream << jump_statement_to_string(jump_statement);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         Statement const &statement) {
  output_stream << statement_to_string(statement);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         CompoundStatement const &compound_statement) {
  output_stream << compound_statement_to_string(compound_statement);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         FunctionDefinition const &function_definition) {
  output_stream << function_definition_to_string(function_definition);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         ExternalDeclaration const &external_declaration) {
  output_stream << external_declaration_to_string(external_declaration);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         TranslationUnit const &translation_unit) {
  output_stream << translation_unit_to_string(translation_unit);
  return output_stream;
}

} // namespace AST
} // namespace Parser

#endif
