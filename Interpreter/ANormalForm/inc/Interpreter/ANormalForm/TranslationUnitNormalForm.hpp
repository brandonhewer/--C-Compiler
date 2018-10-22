#ifndef __TRANSLATION_UNIT_NORMAL_FORM_HPP_
#define __TRANSLATION_UNIT_NORMAL_FORM_HPP_

#include "Interpreter/ANormalForm/StatementNormalForm.hpp"

#include <algorithm>

namespace {

struct ExternalDeclarationToNormal : public boost::static_visitor<> {

  template <typename Vector>
  void operator()(Vector &output,
                  FunctionDefinition const &function_definition) const {
    add_a_normal_function_definition(function_definition, output);
  }

  template <typename Vector>
  void operator()(Vector &output, Declaration const &declaration) const {
    add_a_normal_declaration(declaration, output);
  }
};

template <typename Vector>
void add_a_normal_external_declaration(
    ExternalDeclaration const &external_declaration, Vector &output) {
  boost::apply_visitor(
      boost::bind(ExternalDeclarationToNormal(), boost::ref(output), _1),
      external_declaration);
}

template <typename Vector>
void add_a_normal_translation_unit(TranslationUnit const &translation_unit,
                                   Vector &output) {
  for (auto &&external_declaration : translation_unit)
    add_a_normal_external_declaration(external_declaration, output);
}

void remove_statements_with_no_semantics(
    std::vector<NormalStatement> &statements);

void remove_statements_with_no_semantics(NormalCompoundStatement &compound) {
  return remove_statements_with_no_semantics(compound.statements);
}

template <typename T>
bool temporary_is_type(TemporaryAssignment const &temporary) {
  try {
    std::visit(OperationToConstant<T>(), temporary.expression);
    return true;
  } catch (std::runtime_error &) {
    return false;
  }
}

bool temporary_is_integer(TemporaryAssignment const &temporary) {
  return temporary_is_type<int>(temporary);
}

bool temporary_is_variable(TemporaryAssignment const &temporary) {
  return temporary_is_type<std::string *>(temporary);
}

struct StatementHasNoSemantics {

  bool operator()(VariableAssignment const &) { return false; }
  bool operator()(VariableDeclaration const &) { return false; }
  bool operator()(FunctionDeclaration const &) { return false; }
  bool operator()(NormalReturn const &) { return false; }
  bool operator()(Parser::AST::JumpKeywords const &) { return false; }

  bool operator()(std::unique_ptr<TemporaryAssignment> const &temporary) {
    return temporary_is_integer(*temporary) ||
           temporary_is_variable(*temporary);
  }

  bool operator()(std::unique_ptr<NormalCompoundStatement> const &compound) {
    remove_statements_with_no_semantics(*compound);
    return compound->statements.empty();
  }

  bool operator()(NormalIf const &if_statement) {
    remove_statements_with_no_semantics(*if_statement.body);
    return if_statement.body->statements.empty();
  }

  bool operator()(NormalIfElse const &if_else) {
    remove_statements_with_no_semantics(*if_else.if_statement.body);
    remove_statements_with_no_semantics(*if_else.else_body);
    return if_else.else_body->statements.empty() &&
           if_else.if_statement.body->statements.empty();
  }

  bool operator()(NormalWhile const &while_statement) {
    remove_statements_with_no_semantics(*while_statement.body);
    return while_statement.body->statements.empty();
  }

  bool operator()(NormalFunctionDefinition const &function_definition) {
    remove_statements_with_no_semantics(*function_definition.body);
    return false;
  }

} statement_has_no_semantics_;

bool statement_has_no_semantics(NormalStatement const &statement) {
  return std::visit(statement_has_no_semantics_, statement);
}

void remove_statements_with_no_semantics(
    std::vector<NormalStatement> &statements) {
  statements.erase(std::remove_if(statements.begin(), statements.end(),
                                  statement_has_no_semantics),
                   statements.end());
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

std::vector<NormalStatement> normalise_translation_unit(
    Parser::AST::TranslationUnit const &translation_unit) {
  std::vector<NormalStatement> normalised;
  add_a_normal_translation_unit(translation_unit, normalised);
  remove_statements_with_no_semantics(normalised);
  return normalised;
}

} // namespace ANormalForm
} // namespace Interpreter

#endif
