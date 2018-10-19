#ifndef __EXPRESSION_NORMAL_FORM_HPP_
#define __EXPRESSION_NORMAL_FORM_HPP_

#include "Interpreter/ANormalForm/Expression.hpp"
#include "Parser/AST/AST.hpp"

#include <boost/bind.hpp>

#include <functional>
#include <variant>

namespace Interpreter {
namespace ANormalForm {

template <typename... Ts>
void add_a_normal_assignment_expression(
    Parser::AST::AssignmentExpression const &assignment_expression,
    std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_expression(Parser::AST::Expression const &,
                             std::vector<Ts...> &);
} // namespace ANormalForm
} // namespace Interpreter

namespace {

using namespace Parser::AST;
using namespace Interpreter::ANormalForm;

auto make_temporary(Operation &&expression) {
  return std::make_unique<TemporaryAssignment>(
      std::forward<Operation>(expression));
}

template <typename F, typename T>
auto bind_first_ref(F const &functor, T &value) {
  return std::bind(functor, std::ref(value), _1);
}

template <typename F, typename T>
auto bind_first_ref_boost(F const &functor, T &value) {
  return boost::bind(functor, boost::ref(value), _1);
}

template <typename... Ts>
void add_a_normal_primary_expression(PrimaryExpression const &,
                                     std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_function_application(FunctionApplication const &,
                                       std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_postfix_expression(PostfixExpression const &,
                                     std::vector<Ts...> &);

template <typename Vector>
void add_a_normal_unary_expression(UnaryExpression const &, Vector &);

template <typename... Ts>
void add_a_normal_modulo(Modulo const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_division(Division const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_multiplication(Multiplication const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_multiplicative_expression(MultiplicativeExpression const &,
                                            std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_subtraction(Subtraction const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_addition(Addition const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_additive_expression(AdditiveExpression const &,
                                      std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_less_than(LessThan const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_greater_than(GreaterThan const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_less_than_or_equal(LessThanOrEqualTo const &,
                                     std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_greater_than_or_equal(GreaterThanOrEqualTo const &,
                                        std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_relational_expression(RelationalExpression const &,
                                        std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_equals(Equals const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_not_equal(NotEqual const &, std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_equality_expression(EqualityExpression const &,
                                      std::vector<Ts...> &);

template <typename... Ts>
void add_a_normal_assignment(Assignment const &, std::vector<Ts...> &);

struct MultiplicativeExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  Multiplication const &multiplication) const {
    add_a_normal_multiplication(multiplication, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, Division const &division) const {
    add_a_normal_division(division, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, Modulo const &modulo) const {
    add_a_normal_modulo(modulo, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  UnaryExpression const &unary_expression) const {
    add_a_normal_unary_expression(unary_expression, output);
  }
};

struct AdditiveExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, Addition const &addition) const {
    add_a_normal_addition(addition, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  Subtraction const &subtraction) const {
    add_a_normal_subtraction(subtraction, output);
  }

  template <typename... Ts>
  void
  operator()(std::vector<Ts...> &output,
             MultiplicativeExpression const &multiplicative_expression) const {
    add_a_normal_multiplicative_expression(multiplicative_expression, output);
  }
};

struct RelationalExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, LessThan const &less_than) const {
    add_a_normal_less_than(less_than, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  GreaterThan const &greater_than) const {
    add_a_normal_greater_than(greater_than, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  LessThanOrEqualTo const &less_than_or_equal_to) const {
    add_a_normal_less_than_or_equal(less_than_or_equal_to, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  GreaterThanOrEqualTo const &greater_than_or_equal_to) const {
    add_a_normal_greater_than_or_equal(greater_than_or_equal_to, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  AdditiveExpression const &additive_expression) const {
    add_a_normal_additive_expression(additive_expression, output);
  }
};

struct EqualityExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, Equals const &equals) const {
    add_a_normal_equals(equals, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, NotEqual const &not_equal) const {
    add_a_normal_not_equal(not_equal, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  RelationalExpression const &relational_expression) const {
    add_a_normal_relational_expression(relational_expression, output);
  }
};

struct AssignmentExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  EqualityExpression const &equality_expression) const {
    add_a_normal_equality_expression(equality_expression, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  Assignment const &assignment) const {
    add_a_normal_assignment(assignment, output);
  }
};

struct FunctionArgumentBuilder {
  FunctionArgumentBuilder(std::vector<Operand> &operands)
      : m_operands(operands) {}

  void operator()(std::unique_ptr<TemporaryAssignment> const &operand) {
    try {
      int constant =
          std::visit(OperationToConstant<int>(), operand->expression);
      m_operands.emplace_back(Operand(constant));
    } catch (std::runtime_error &) {
      m_operands.emplace_back(operand.get());
    }
  }

  void operator()(VariableAssignment const &operand) {
    m_operands.emplace_back(operand.variable);
  }

  template <typename T> void operator()(T const &) {
    throw std::runtime_error(
        "Attempted to pass invalid operands to function call.");
  }

private:
  std::vector<Operand> &m_operands;
};

template <typename Vector>
FunctionCall create_normal_function_call(
    std::variant<std::string *, TemporaryAssignment const *> identifier,
    Expression const &argument_list, Vector &output) {
  std::vector<Operand> arguments;
  arguments.reserve(argument_list.size());

  auto add_argument = FunctionArgumentBuilder(arguments);
  for (auto &&argument : argument_list) {
    add_a_normal_assignment_expression(argument, output);
    std::visit(add_argument, output.back());
  }
  return FunctionCall{identifier, std::move(arguments)};
}

template <typename Vector>
void function_call_to_temporary(
    std::variant<std::string *, TemporaryAssignment const *> identifier,
    Expression const &argument_list, Vector &output) {
  output.emplace_back(make_temporary(
      create_normal_function_call(identifier, argument_list, output)));
}

template <typename Vector>
void function_call_to_temporary(Expression const &argument_list,
                                Vector &output) {
  auto &temporary =
      std::get<std::unique_ptr<TemporaryAssignment>>(output.back());
  output.emplace_back(make_temporary(
      create_normal_function_call(temporary.get(), argument_list, output)));
}

template <typename Vector, typename StartIt, typename EndIt>
void function_calls_to_temporaries(StartIt start_args, EndIt end_args,
                                   Vector &output) {
  for (auto it = start_args; it < end_args; ++it)
    function_call_to_temporary(*it, output);
}

template <typename Vector>
void function_calls_to_normal(
    std::variant<std::string *, TemporaryAssignment const *> identifier,
    std::vector<Expression> const &argument_lists, Vector &output) {
  if (argument_lists.empty()) {
    output.emplace_back(make_temporary(FunctionCall{identifier, {}}));
    return;
  }

  function_call_to_temporary(identifier, argument_lists.front(), output);
  function_calls_to_temporaries(argument_lists.begin() + 1,
                                argument_lists.end(), output);
}

struct GetFunctionIdentifier {
  std::variant<std::string *, TemporaryAssignment const *>
  operator()(std::unique_ptr<TemporaryAssignment> const &assignment) const {
    try {
      return temporary_to_variable(assignment.get());
    } catch (std::runtime_error &) {
      return assignment.get();
    }
  }

  std::variant<std::string *, TemporaryAssignment const *>
  operator()(VariableAssignment const &assignment) const {
    return assignment.variable;
  }

  template <typename T>
  std::variant<std::string *, TemporaryAssignment const *>
  operator()(T const &) const {
    throw std::runtime_error(
        "called object is not a function or function pointer");
  }
};

struct FunctionApplicationToNormal : public boost::static_visitor<> {
  FunctionApplicationToNormal(std::vector<Expression> const &argument_lists)
      : m_argument_lists(argument_lists) {}

  template <typename Vector>
  void operator()(Vector &output, Expression const &expression) const {
    add_a_normal_expression(expression, output);
    auto identifier = std::visit(GetFunctionIdentifier(), output.back());
    function_calls_to_normal(identifier, m_argument_lists, output);
  }

  template <typename Vector>
  void operator()(Vector &output, std::string *identifier) const {
    function_calls_to_normal(identifier, m_argument_lists, output);
  }

  template <typename... Ts> void operator()(std::vector<Ts...> &, int) {
    throw std::runtime_error("integer is not a function or function pointer");
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &, std::string const &) {
    throw std::runtime_error(
        "string literal is not a function or function pointer");
  }

private:
  std::vector<Expression> const &m_argument_lists;
};

struct PrimaryExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  Expression const &expression) const {
    add_a_normal_expression(expression, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, std::string const &) const {
    throw std::runtime_error("cannot use string literal in postfix expression");
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, std::string *operand) const {
    output.emplace_back(make_temporary(Operand(operand)));
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, int operand) const {
    output.emplace_back(make_temporary(Operand(operand)));
  }
};

struct PostfixExpressionToNormal : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  PrimaryExpression const &primary_expression) const {
    add_a_normal_primary_expression(primary_expression, output);
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  FunctionApplication const &application) const {
    add_a_normal_function_application(application, output);
  }
};

template <typename... Ts>
void add_unary_operation(UnaryOperators op, Operand operand,
                         std::vector<Ts...> &output) {
  output.emplace_back(make_temporary(UnaryOperation{op, std::move(operand)}));
}

template <typename Vector>
void add_unary_expression(std::vector<UnaryOperators> const &operators,
                          Operand operand, Vector &output) {
  add_unary_operation(operators.back(), operand, output);

  for (auto it = operators.rbegin() + 1; it < operators.rend(); ++it) {
    auto &temporary =
        std::get<std::unique_ptr<TemporaryAssignment>>(output.back());
    add_unary_operation(*it, temporary.get(), output);
  }
}

template <typename Vector> struct AddUnaryExpression {
  AddUnaryExpression(Vector &output,
                     std::vector<UnaryOperators> const &operators)
      : m_output(output), m_operators(simplify_unary_operators(operators)) {}

  void operator()(VariableAssignment const &operand) {
    try {
      m_output.emplace_back(make_temporary(
          Operand(evaluate_unary_constant(m_operators, operand))));
    } catch (std::runtime_error &) {
      add_unary_expression(m_operators, operand.variable, m_output);
    }
  }

  void operator()(std::unique_ptr<TemporaryAssignment> const &operand) {
    try {
      m_output.emplace_back(make_temporary(
          Operand(evaluate_unary_constant(m_operators, operand.get()))));
    } catch (std::runtime_error &) {
      add_unary_expression(m_operators, operand.get(), m_output);
    }
  }

  template <typename T> void operator()(T const &val) {
    throw std::runtime_error(
        "attempted to create unary expression from invalid operand");
  }

private:
  Vector &m_output;
  std::vector<UnaryOperators> m_operators;
};

struct CreateBinaryOperation {
  CreateBinaryOperation(BinaryOperators op) : m_operator(op) {}

  Operation operator()(VariableAssignment const &lhs,
                       std::unique_ptr<TemporaryAssignment> const &rhs) const {
    return create_simplified_binary(m_operator, lhs, rhs.get());
  }

  Operation operator()(std::unique_ptr<TemporaryAssignment> const &lhs,
                       VariableAssignment const &rhs) const {
    return create_simplified_binary(m_operator, lhs.get(), rhs);
  }

  Operation operator()(std::unique_ptr<TemporaryAssignment> const &lhs,
                       std::unique_ptr<TemporaryAssignment> const &rhs) const {
    return create_simplified_binary(m_operator, lhs.get(), rhs.get());
  }

  Operation operator()(VariableAssignment const &lhs,
                       VariableAssignment const &rhs) const {
    return create_simplified_binary(m_operator, lhs, rhs);
  }

  template <typename T, typename U>
  Operation operator()(T const &, U const &) const {
    throw std::runtime_error(
        "Attempted to create binary expression from invalid operands.");
  }

private:
  BinaryOperators m_operator;
};

struct AddNormalAssignment : public boost::static_visitor<> {

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, VariableAssignment const &lhs,
                  std::unique_ptr<TemporaryAssignment> const &rhs) const {
    output.emplace_back(
        VariableAssignment{lhs.variable, simplify_temporary(rhs.get())});
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  std::unique_ptr<TemporaryAssignment> const &lhs,
                  VariableAssignment const &rhs) const {
    try {
      output.emplace_back(VariableAssignment{temporary_to_variable(lhs.get()),
                                             simplify_variable(rhs)});
    } catch (std::runtime_error &) {
      output.emplace_back(make_temporary(simplify_variable(rhs)));
    }
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  std::unique_ptr<TemporaryAssignment> const &lhs,
                  std::unique_ptr<TemporaryAssignment> const &rhs) const {
    try {
      output.emplace_back(VariableAssignment{temporary_to_variable(lhs.get()),
                                             simplify_temporary(rhs.get())});
    } catch (std::runtime_error &) {
      output.emplace_back(make_temporary(simplify_temporary(rhs.get())));
    }
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, VariableAssignment const &lhs,
                  VariableAssignment const &rhs) const {
    output.emplace_back(
        VariableAssignment{lhs.variable, simplify_variable(rhs)});
  }

  template <typename T, typename U, typename... Ts>
  void operator()(std::vector<Ts...> &, T const &, U const &) const {
    throw std::runtime_error(
        "unable to create assignment from invalid operands");
  }
};

template <typename... Ts>
void add_a_normal_primary_expression(
    PrimaryExpression const &primary_expression, std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(PrimaryExpressionToNormal(), output),
      primary_expression);
}

template <typename... Ts>
void add_a_normal_function_application(FunctionApplication const &application,
                                       std::vector<Ts...> &output) {
  auto application_to_normal = bind_first_ref_boost(
      FunctionApplicationToNormal(application.argument_lists), output);
  boost::apply_visitor(application_to_normal, application.identifier);
}

template <typename... Ts>
void add_a_normal_postfix_expression(
    Parser::AST::PostfixExpression const &postfix_expression,
    std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(PostfixExpressionToNormal(), output),
      postfix_expression);
}

template <typename Vector>
void add_a_normal_unary_expression(
    Parser::AST::UnaryExpression const &unary_expression, Vector &output) {
  add_a_normal_postfix_expression(unary_expression.expression, output);

  if (!unary_expression.operators.empty())
    std::visit(AddUnaryExpression(output, unary_expression.operators),
               output.back());
}

template <typename T, typename Vector>
void add_normal_binary(BinaryOperators op, T const &left_assign,
                       T const &right_assign, Vector &output) {
  auto binary_operation =
      std::visit(CreateBinaryOperation(op), left_assign, right_assign);
  auto temporary = make_temporary(std::move(binary_operation));
  output.emplace_back(std::move(temporary));
}

template <typename Multiplicative, typename Vector>
void add_normal_multiplicative(Multiplicative const &multiplicative,
                               BinaryOperators op, Vector &output) {
  add_a_normal_unary_expression(multiplicative.lhs, output);
  auto const left_assign = output.size() - 1;
  add_a_normal_multiplicative_expression(multiplicative.rhs.get(), output);
  add_normal_binary(op, output[left_assign], output.back(), output);
}

template <typename Additive, typename... Ts>
void add_normal_additive(Additive const &additive, BinaryOperators op,
                         std::vector<Ts...> &output) {
  add_a_normal_multiplicative_expression(additive.lhs, output);
  auto const left_assign = output.size() - 1;
  add_a_normal_additive_expression(additive.rhs.get(), output);
  add_normal_binary(op, output[left_assign], output.back(), output);
}

template <typename Relational, typename... Ts>
void add_normal_relational(Relational const &relational, BinaryOperators op,
                           std::vector<Ts...> &output) {
  add_a_normal_additive_expression(relational.lhs, output);
  auto const left_assign = output.size() - 1;
  add_a_normal_relational_expression(relational.rhs.get(), output);
  add_normal_binary(op, output[left_assign], output.back(), output);
}

template <typename Equality, typename... Ts>
void add_normal_equality(Equality const &equality, BinaryOperators op,
                         std::vector<Ts...> &output) {
  add_a_normal_relational_expression(equality.lhs, output);
  auto const left_assign = output.size() - 1;
  add_a_normal_equality_expression(equality.rhs.get(), output);
  add_normal_binary(op, output[left_assign], output.back(), output);
}

template <typename... Ts>
void add_a_normal_modulo(Parser::AST::Modulo const &modulo,
                         std::vector<Ts...> &output) {
  add_normal_multiplicative(modulo, BinaryOperators::MODULO, output);
}

template <typename... Ts>
void add_a_normal_division(Parser::AST::Division const &division,
                           std::vector<Ts...> &output) {
  add_normal_multiplicative(division, BinaryOperators::DIVISION, output);
}

template <typename... Ts>
void add_a_normal_multiplication(
    Parser::AST::Multiplication const &multiplication,
    std::vector<Ts...> &output) {
  add_normal_multiplicative(multiplication, BinaryOperators::MULTIPLICATION,
                            output);
}

template <typename... Ts>
void add_a_normal_multiplicative_expression(
    Parser::AST::MultiplicativeExpression const &multiplicative_expression,
    std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(MultiplicativeExpressionToNormal(), output),
      multiplicative_expression);
}

template <typename... Ts>
void add_a_normal_subtraction(Parser::AST::Subtraction const &subtraction,
                              std::vector<Ts...> &output) {
  add_normal_additive(subtraction, BinaryOperators::SUBTRACTION, output);
}

template <typename... Ts>
void add_a_normal_addition(Parser::AST::Addition const &addition,
                           std::vector<Ts...> &output) {
  add_normal_additive(addition, BinaryOperators::ADDITION, output);
}

template <typename... Ts>
void add_a_normal_additive_expression(
    Parser::AST::AdditiveExpression const &additive_expression,
    std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(AdditiveExpressionToNormal(), output),
      additive_expression);
}

template <typename... Ts>
void add_a_normal_less_than(Parser::AST::LessThan const &less_than,
                            std::vector<Ts...> &output) {
  add_normal_relational(less_than, BinaryOperators::LESS_THAN, output);
}

template <typename... Ts>
void add_a_normal_greater_than(Parser::AST::GreaterThan const &greater_than,
                               std::vector<Ts...> &output) {
  add_normal_relational(greater_than, BinaryOperators::GREATER_THAN, output);
}

template <typename... Ts>
void add_a_normal_less_than_or_equal(
    Parser::AST::LessThanOrEqualTo const &less_than_or_equal_to,
    std::vector<Ts...> &output) {
  add_normal_relational(less_than_or_equal_to,
                        BinaryOperators::LESS_THAN_OR_EQUAL_TO, output);
}

template <typename... Ts>
void add_a_normal_greater_than_or_equal(
    Parser::AST::GreaterThanOrEqualTo const &greater_than_or_equal_to,
    std::vector<Ts...> &output) {
  add_normal_relational(greater_than_or_equal_to,
                        BinaryOperators::GREATER_THAN_OR_EQUAL_TO, output);
}

template <typename... Ts>
void add_a_normal_relational_expression(
    Parser::AST::RelationalExpression const &relational_expression,
    std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(RelationalExpressionToNormal(), output),
      relational_expression);
}

template <typename... Ts>
void add_a_normal_equals(Parser::AST::Equals const &equals,
                         std::vector<Ts...> &output) {
  add_normal_equality(equals, BinaryOperators::EQUALS, output);
}

template <typename... Ts>
void add_a_normal_not_equal(Parser::AST::NotEqual const &not_equal,
                            std::vector<Ts...> &output) {
  add_normal_equality(not_equal, BinaryOperators::NOT_EQUAL, output);
}

template <typename... Ts>
void add_a_normal_equality_expression(
    Parser::AST::EqualityExpression const &equality_expression,
    std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(EqualityExpressionToNormal(), output),
      equality_expression);
}

template <typename... Ts>
void add_a_normal_assignment(Parser::AST::Assignment const &assignment,
                             std::vector<Ts...> &output) {
  add_a_normal_unary_expression(assignment.lhs, output);

  auto const left_assign = output.size() - 1;
  add_a_normal_assignment_expression(assignment.rhs.get(), output);
  auto add_normal_assignment =
      boost::bind(AddNormalAssignment(), boost::ref(output), _1, _2);
  std::visit(add_normal_assignment, output[left_assign], output.back());
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

template <typename... Ts>
void add_a_normal_assignment_expression(
    Parser::AST::AssignmentExpression const &assignment_expression,
    std::vector<Ts...> &output) {
  boost::apply_visitor(
      bind_first_ref_boost(AssignmentExpressionToNormal(), output),
      assignment_expression);
}

template <typename... Ts>
void add_a_normal_expression(Parser::AST::Expression const &expression,
                             std::vector<Ts...> &output) {
  for (auto &&assignment_expression : expression)
    add_a_normal_assignment_expression(assignment_expression, output);
}

} // namespace ANormalForm
} // namespace Interpreter

#endif
