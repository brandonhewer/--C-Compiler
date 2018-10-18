#include "Interpreter/ANormalForm/Expression.hpp"

#include <optional>

namespace {

using namespace Interpreter::ANormalForm;
using Parser::AST::UnaryOperators;

int evaluate_constant(UnaryOperators op, int operand) {
  switch (op) {
  case UnaryOperators::POSITIVE:
    return operand;
  case UnaryOperators::NEGATIVE:
    return -operand;
  case UnaryOperators::INVERSION:
    return !operand;
  default:
    throw std::runtime_error("Invalid operator used on integer constant.");
  }
}

int evaluate_constant(BinaryOperators op, int lhs, int rhs) {
  switch (op) {
  case BinaryOperators::ADDITION:
    return lhs + rhs;
  case BinaryOperators::SUBTRACTION:
    return lhs - rhs;
  case BinaryOperators::MULTIPLICATION:
    return lhs * rhs;
  case BinaryOperators::DIVISION:
    return lhs / rhs;
  case BinaryOperators::MODULO:
    return lhs % rhs;
  case BinaryOperators::LESS_THAN:
    return static_cast<int>(lhs < rhs);
  case BinaryOperators::GREATER_THAN:
    return static_cast<int>(lhs > rhs);
  case BinaryOperators::LESS_THAN_OR_EQUAL_TO:
    return static_cast<int>(lhs <= rhs);
  case BinaryOperators::GREATER_THAN_OR_EQUAL_TO:
    return static_cast<int>(lhs >= rhs);
  case BinaryOperators::EQUALS:
    return static_cast<int>(lhs == rhs);
  case BinaryOperators::NOT_EQUAL:
    return static_cast<int>(lhs != rhs);
  }
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

int evaluate_binary_expression(BinaryOperators op, int lhs, int rhs) {
  return evaluate_constant(op, lhs, rhs);
}

int evaluate_unary_expression(Parser::AST::UnaryOperators op, int operand) {
  return evaluate_constant(op, operand);
}

} // namespace ANormalForm
} // namespace Interpreter
