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

TemporaryAssignment const *
get_assignment_from_temporary(TemporaryAssignment const *temporary) {
  try {
    auto operand = std::get<Operand>(temporary->expression);
    return std::get<TemporaryAssignment const *>(operand);
  } catch (std::bad_variant_access &) {
    return nullptr;
  }
}

template <typename T>
T temporary_to_constant(TemporaryAssignment const *assignment) {
  TemporaryAssignment const *current = assignment;

  while (nullptr != current) {
    try {
      return std::visit(OperationToConstant<T>(), current->expression);
    } catch (std::runtime_error &) {
      current = get_assignment_from_temporary(current);
    }
  }
  throw std::runtime_error("assignment is not a constant");
}

Operand get_variable_or_temporary(TemporaryAssignment const *assignment) {
  try {
    return temporary_to_constant<std::string *>(assignment);
  } catch (std::runtime_error &) {
    return assignment;
  }
}

template <typename T>
T variable_to_constant(VariableAssignment const &variable) {
  return std::visit(OperationToConstant<int>(), variable.expression);
}

Operation create_simplified_binary_partial(BinaryOperators op, int lhs,
                                           VariableAssignment const &rhs) {
  try {
    return evaluate_constant(op, lhs, variable_to_constant<int>(rhs));
  } catch (std::runtime_error &) {
    return BinaryOperation{op, Operand(lhs), Operand(rhs.variable)};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op, int lhs,
                                           TemporaryAssignment const *rhs) {
  try {
    return evaluate_constant(op, lhs, temporary_to_constant<int>(rhs));
  } catch (std::runtime_error &) {
    return BinaryOperation{op, Operand(lhs), get_variable_or_temporary(rhs)};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op,
                                           VariableAssignment const &lhs,
                                           Operand rhs) {
  try {
    return BinaryOperation{op, Operand(variable_to_constant<int>(lhs)),
                           std::move(rhs)};
  } catch (std::runtime_error &) {
    return BinaryOperation{op, Operand(lhs.variable), std::move(rhs)};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op, Operand lhs,
                                           VariableAssignment const &rhs) {
  try {
    return BinaryOperation{op, std::move(lhs),
                           Operand(variable_to_constant<int>(rhs))};
  } catch (std::runtime_error &) {
    return BinaryOperation{op, std::move(lhs), Operand(rhs.variable)};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op, Operand lhs,
                                           TemporaryAssignment const *rhs) {
  try {
    return BinaryOperation{op, std::move(lhs),
                           Operand(temporary_to_constant<int>(rhs))};
  } catch (std::runtime_error &) {
    return BinaryOperation{op, std::move(lhs), get_variable_or_temporary(rhs)};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op,
                                           TemporaryAssignment const *lhs,
                                           std::string *rhs) {
  try {
    return BinaryOperation{op, Operand(temporary_to_constant<int>(lhs)),
                           Operand(rhs)};
  } catch (std::runtime_error &) {
    return BinaryOperation{op, get_variable_or_temporary(lhs), rhs};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op, std::string *lhs,
                                           TemporaryAssignment const *rhs) {
  try {
    return BinaryOperation{op, Operand(lhs),
                           Operand(temporary_to_constant<int>(rhs))};
  } catch (std::runtime_error &) {
    return BinaryOperation{op, lhs, get_variable_or_temporary(rhs)};
  }
}

Operation create_simplified_binary_partial(BinaryOperators op, std::string *lhs,
                                           VariableAssignment const &rhs) {
  try {
    return BinaryOperation{op, Operand(lhs),
                           Operand(variable_to_constant<int>(rhs))};
  } catch (std::runtime_error &) {
    return BinaryOperation{op, Operand(lhs), Operand(rhs.variable)};
  }
}

std::vector<UnaryOperators> get_unary_operators(bool switch_sign,
                                                std::size_t inversions) {
  std::vector<UnaryOperators> operators;
  if (switch_sign)
    operators.emplace_back(UnaryOperators::NEGATIVE);
  for (auto i = 0u; i < inversions; ++i)
    operators.emplace_back(UnaryOperators::INVERSION);
  return operators;
}

int calculate_unary_constant(std::vector<UnaryOperators> const &operators,
                             int constant) {
  for (auto &&op : operators)
    constant = evaluate_constant(op, constant);
  return constant;
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

std::string *temporary_to_variable(TemporaryAssignment const *temporary) {
  return temporary_to_constant<std::string *>(temporary);
}

Operand simplify_temporary(TemporaryAssignment const *assignment) {
  try {
    return temporary_to_constant<int>(assignment);
  } catch (std::runtime_error &) {
    return get_variable_or_temporary(assignment);
  }
}

Operand simplify_variable(VariableAssignment const &assignment) {
  try {
    return variable_to_constant<int>(assignment);
  } catch (std::runtime_error &) {
    return assignment.variable;
  }
}

Operation create_simplified_binary(BinaryOperators op,
                                   TemporaryAssignment const *lhs,
                                   VariableAssignment const &rhs) {
  try {
    return create_simplified_binary_partial(op, temporary_to_constant<int>(lhs),
                                            rhs);
  } catch (std::runtime_error &) {
    return create_simplified_binary_partial(op, get_variable_or_temporary(lhs),
                                            rhs);
  }
}

Operation create_simplified_binary(BinaryOperators op,
                                   VariableAssignment const &lhs,
                                   TemporaryAssignment const *rhs) {
  try {
    return create_simplified_binary_partial(op, variable_to_constant<int>(lhs),
                                            rhs);
  } catch (std::runtime_error &) {
    return create_simplified_binary_partial(op, lhs.variable, rhs);
  }
}

Operation create_simplified_binary(BinaryOperators op,
                                   VariableAssignment const &lhs,
                                   VariableAssignment const &rhs) {
  try {
    return create_simplified_binary_partial(op, variable_to_constant<int>(lhs),
                                            rhs);
  } catch (std::runtime_error &) {
    return create_simplified_binary_partial(op, lhs.variable, rhs);
  }
}

Operation create_simplified_binary(BinaryOperators op,
                                   TemporaryAssignment const *lhs,
                                   TemporaryAssignment const *rhs) {
  try {
    return create_simplified_binary_partial(op, temporary_to_constant<int>(lhs),
                                            rhs);
  } catch (std::runtime_error &) {
    return create_simplified_binary_partial(op, get_variable_or_temporary(lhs),
                                            rhs);
  }
}

std::vector<UnaryOperators>
simplify_unary_operators(std::vector<UnaryOperators> const &operators) {
  bool switch_sign = false;
  std::size_t inversion_count = 0;

  for (auto it = operators.rbegin(); it < operators.rend(); ++it) {
    if (*it == UnaryOperators::INVERSION) {
      switch_sign = false;
      ++inversion_count;
    } else if (*it == UnaryOperators::NEGATIVE)
      switch_sign = !switch_sign;
  }
  return get_unary_operators(switch_sign, inversion_count);
}

int evaluate_unary_constant(
    std::vector<Parser::AST::UnaryOperators> const &operators,
    VariableAssignment const &assignment) {
  return calculate_unary_constant(operators,
                                  variable_to_constant<int>(assignment));
}

int evaluate_unary_constant(
    std::vector<Parser::AST::UnaryOperators> const &operators,
    TemporaryAssignment const *temporary) {
  return calculate_unary_constant(operators,
                                  temporary_to_constant<int>(temporary));
}

} // namespace ANormalForm
} // namespace Interpreter
