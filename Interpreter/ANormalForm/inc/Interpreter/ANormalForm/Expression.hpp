#ifndef __EXPRESSION_HPP_
#define __EXPRESSION_HPP_

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
  Operation expression;
};

struct VariableAssignment {
  std::string *variable;
  Operation expression;
};

int evaluate_binary_expression(BinaryOperators op, int lhs, int rhs);
int evaluate_unary_expression(Parser::AST::UnaryOperators op, int operand);

} // namespace ANormalForm
} // namespace Interpreter

#endif
