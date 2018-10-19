#ifndef __ANORMAL_EXPRESSION_HPP_
#define __ANORMAL_EXPRESSION_HPP_

#include "Parser/AST/Expression.hpp"

#include <variant>
#include <vector>

namespace Interpreter {
namespace ANormalForm {

struct TemporaryAssignment;

using Operand = std::variant<std::string *, TemporaryAssignment const *, int>;

enum class BinaryOperators {
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  MODULO,
  LESS_THAN,
  GREATER_THAN,
  LESS_THAN_OR_EQUAL_TO,
  GREATER_THAN_OR_EQUAL_TO,
  EQUALS,
  NOT_EQUAL
};

struct BinaryOperation {
  BinaryOperators op;
  Operand lhs;
  Operand rhs;
};

struct UnaryOperation {
  Parser::AST::UnaryOperators op;
  Operand operand;
};

struct FunctionCall {
  std::variant<std::string *, TemporaryAssignment const *> function_identifier;
  std::vector<Operand> operands;
};

using Operation =
    std::variant<UnaryOperation, BinaryOperation, FunctionCall, Operand>;

struct TemporaryAssignment {
  TemporaryAssignment(Operation exp) : expression(std::move(exp)) {}
  Operation expression;
};

struct VariableAssignment {
  std::string *variable;
  Operation expression;
};

template <typename T> T operand_to_constant(Operand const &operand) {
  try {
    return std::get<T>(operand);
  } catch (std::bad_variant_access &) {
    throw std::runtime_error("operand is not of the correct constant type.");
  }
}

template <typename T> struct OperationToConstant {
  T operator()(Operand const &operand) const {
    return operand_to_constant<T>(operand);
  }

  T operator()(UnaryOperation const &) {
    throw std::runtime_error("temporary is a unary operation");
  }

  T operator()(BinaryOperation const &) {
    throw std::runtime_error("temporary is a binary operation");
  }

  T operator()(FunctionCall const &) {
    throw std::runtime_error("temporary is a function call");
  }
};

std::string *temporary_to_variable(TemporaryAssignment const *);

Operand simplify_temporary(TemporaryAssignment const *);
Operand simplify_variable(VariableAssignment const &);
Operation create_simplified_binary(BinaryOperators, TemporaryAssignment const *,
                                   VariableAssignment const &);
Operation create_simplified_binary(BinaryOperators, VariableAssignment const &,
                                   TemporaryAssignment const *);
Operation create_simplified_binary(BinaryOperators, VariableAssignment const &,
                                   VariableAssignment const &);
Operation create_simplified_binary(BinaryOperators, TemporaryAssignment const *,
                                   TemporaryAssignment const *);

std::vector<Parser::AST::UnaryOperators> simplify_unary_operators(
    std::vector<Parser::AST::UnaryOperators> const &operators);

int evaluate_unary_constant(
    std::vector<Parser::AST::UnaryOperators> const &operators,
    VariableAssignment const &);
int evaluate_unary_constant(
    std::vector<Parser::AST::UnaryOperators> const &operators,
    TemporaryAssignment const *);

} // namespace ANormalForm
} // namespace Interpreter

#endif
