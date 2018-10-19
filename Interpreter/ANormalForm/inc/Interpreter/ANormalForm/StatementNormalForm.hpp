#ifndef __STATEMENT_NORMAL_FORM_HPP_
#define __STATEMENT_NORMAL_FORM_HPP_

#include "Interpreter/ANormalForm/DeclarationNormalForm.hpp"
#include "Interpreter/ANormalForm/Statement.hpp"

namespace Interpreter {
namespace ANormalForm {

template <typename Vector>
void add_a_normal_function_definition(
    FunctionDefinition const &function_definition, Vector &output);

template <typename Vector>
void add_a_normal_statement(Parser::AST::Statement const &, Vector &);
template <typename Vector>
void add_a_normal_declaration(Parser::AST::Declaration const &declaration,
                              Vector &output);

std::unique_ptr<NormalCompoundStatement>
create_a_normal_compound_statement(Parser::AST::Statement const &);
std::unique_ptr<NormalCompoundStatement>
create_a_normal_compound_statement(Parser::AST::CompoundStatement const &);

} // namespace ANormalForm
} // namespace Interpreter

namespace {

using namespace Interpreter::ANormalForm;
using namespace Parser::AST;

struct ExtractOperand {
  Operand operator()(std::unique_ptr<TemporaryAssignment> const &temporary) {
    return simplify_temporary(temporary.get());
  }

  Operand operator()(VariableAssignment const &assignment) {
    return simplify_variable(assignment);
  }

  template <typename T> Operand operator()(T const &) {
    throw std::runtime_error("invalid statement provided to conditional");
  }
} extract_operand_;

template <typename T> Operand extract_operand(T const &condition) {
  return std::visit(extract_operand_, condition);
}

template <typename Vector>
void add_a_normal_if(If const &if_statement, Vector &output) {
  add_a_normal_expression(if_statement.condition, output);
  output.emplace_back(
      NormalIf{extract_operand(output.back()),
               create_a_normal_compound_statement(if_statement.body.get())});
}

template <typename Vector>
void add_a_normal_if_else(IfElse const &if_else, Vector &output) {
  add_a_normal_expression(if_else.if_statement.condition, output);
  output.emplace_back(NormalIfElse{
      NormalIf{
          extract_operand(output.back()),
          create_a_normal_compound_statement(if_else.if_statement.body.get())},
      create_a_normal_compound_statement(if_else.else_body.get())});
}

template <typename Vector>
void add_a_normal_while(While const &while_statement, Vector &output) {
  add_a_normal_expression(while_statement.condition, output);
  output.emplace_back(NormalWhile{
      extract_operand(output.back()),
      create_a_normal_compound_statement(while_statement.body.get())});
}

template <typename Vector>
void add_a_normal_return(Return const &return_statement, Vector &output) {
  if (return_statement.expression.empty())
    output.emplace_back(NormalReturn{});
  else {
    add_a_normal_expression(return_statement.expression, output);
    output.emplace_back(NormalReturn{extract_operand(output.back())});
  }
}

struct JumpStatementToNormal : public boost::static_visitor<> {

  template <typename Vector>
  void operator()(Vector &output, JumpKeywords const &keyword) const {
    output.emplace_back(keyword);
  }

  template <typename Vector>
  void operator()(Vector &output, Return const &return_statement) const {
    add_a_normal_return(return_statement, output);
  }
};

template <typename Vector>
void add_a_normal_jump_statement(JumpStatement const &statement,
                                 Vector &output) {
  auto add_normal_jump =
      boost::bind(JumpStatementToNormal(), boost::ref(output), _1);
  boost::apply_visitor(add_normal_jump, statement);
}

struct StatementToNormal : public boost::static_visitor<> {

  template <typename Vector>
  void operator()(Vector &output, CompoundStatement const &statement) const {
    output.emplace_back(create_a_normal_compound_statement(statement));
  }

  template <typename Vector>
  void operator()(Vector &output, Expression const &expression) const {
    add_a_normal_expression(expression, output);
  }

  template <typename Vector>
  void operator()(Vector &output, If const &if_statement) const {
    add_a_normal_if(if_statement, output);
  }

  template <typename Vector>
  void operator()(Vector &output, IfElse const &if_else) const {
    add_a_normal_if_else(if_else, output);
  }

  template <typename Vector>
  void operator()(Vector &output, While const &while_statement) const {
    add_a_normal_while(while_statement, output);
  }

  template <typename Vector>
  void operator()(Vector &output, JumpStatement const &jump_statement) const {
    add_a_normal_jump_statement(jump_statement, output);
  }
};

struct DeclarationStatementOrFunctionToNormal : public boost::static_visitor<> {

  template <typename Vector>
  void operator()(Vector &output, Declaration const &declaration) const {
    add_a_normal_declaration(declaration, output);
  }

  template <typename Vector>
  void operator()(Vector &output,
                  x3::forward_ast<Statement> const &statement) const {
    add_a_normal_statement(statement.get(), output);
  }

  template <typename Vector>
  void operator()(Vector &output, FunctionDefinition const &definition) const {
    add_a_normal_function_definition(definition, output);
  }
};

template <typename Vector>
void add_a_normal_declaration_statement_or_function(
    DeclarationStatementOrFunction const &declaration_statement_or_function,
    Vector &output) {
  auto normal_declaration_statement_or_function = boost::bind(
      DeclarationStatementOrFunctionToNormal(), boost::ref(output), _1);
  boost::apply_visitor(normal_declaration_statement_or_function,
                       declaration_statement_or_function);
}

struct CreateCompoundStatement
    : public boost::static_visitor<std::unique_ptr<NormalCompoundStatement>> {

  std::unique_ptr<NormalCompoundStatement>
  operator()(CompoundStatement const &compound_statement) {
    return create_a_normal_compound_statement(compound_statement);
  }

  std::unique_ptr<NormalCompoundStatement>
  operator()(Expression const &expression) const {
    auto compound_statement = std::make_unique<NormalCompoundStatement>();
    add_a_normal_expression(expression, compound_statement->statements);
    return std::move(compound_statement);
  }

  std::unique_ptr<NormalCompoundStatement>
  operator()(If const &if_statement) const {
    auto compound_statement = std::make_unique<NormalCompoundStatement>();
    add_a_normal_if(if_statement, compound_statement->statements);
    return std::move(compound_statement);
  }

  std::unique_ptr<NormalCompoundStatement>
  operator()(IfElse const &if_else) const {
    auto compound_statement = std::make_unique<NormalCompoundStatement>();
    add_a_normal_if_else(if_else, compound_statement->statements);
    return std::move(compound_statement);
  }

  std::unique_ptr<NormalCompoundStatement>
  operator()(While const &while_statement) const {
    auto compound_statement = std::make_unique<NormalCompoundStatement>();
    add_a_normal_while(while_statement, compound_statement->statements);
    return std::move(compound_statement);
  }

  std::unique_ptr<NormalCompoundStatement>
  operator()(JumpStatement const &jump_statement) const {
    auto compound_statement = std::make_unique<NormalCompoundStatement>();
    add_a_normal_jump_statement(jump_statement, compound_statement->statements);
    return std::move(compound_statement);
  }
} create_compound_statement_;

} // namespace

namespace Interpreter {
namespace ANormalForm {

template <typename Vector>
void add_a_normal_function_definition(
    FunctionDefinition const &function_definition, Vector &output) {
  auto const specifiers =
      simplify_declaration_specifiers(function_definition.specifiers);
  auto declaration =
      FunctionDeclaration{function_definition.declarator.identifier,
                          specifiers.second, specifiers.first,
                          parameters_or_identifiers_to_declarations(
                              function_definition.declarator.parameters)};
  output.emplace_back(NormalFunctionDefinition{
      std::move(declaration),
      create_a_normal_compound_statement(function_definition.body)});
}

template <typename Vector>
void add_a_normal_statement(Parser::AST::Statement const &statement,
                            Vector &output) {
  boost::apply_visitor(boost::bind(StatementToNormal(), boost::ref(output), _1),
                       statement);
}

std::unique_ptr<NormalCompoundStatement>
create_a_normal_compound_statement(Parser::AST::Statement const &statement) {
  return boost::apply_visitor(create_compound_statement_, statement);
}

std::unique_ptr<NormalCompoundStatement> create_a_normal_compound_statement(
    Parser::AST::CompoundStatement const &compound_statement) {
  auto normal_statement = std::make_unique<NormalCompoundStatement>();
  auto &statements = normal_statement->statements;

  for (auto &&statement : compound_statement)
    add_a_normal_declaration_statement_or_function(statement, statements);
  return std::move(normal_statement);
}

} // namespace ANormalForm
} // namespace Interpreter

#endif
