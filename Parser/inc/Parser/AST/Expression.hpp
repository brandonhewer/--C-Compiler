#ifndef __EXPRESSION_H
#define __EXPRESSION_H

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

namespace x3 = boost::spirit::x3;

namespace Parser {
namespace AST {

struct AdditiveExpression;
struct AssignmentExpression;
struct EqualityExpression;
struct MultiplicativeExpression;
struct RelationalExpression;

using Expression = std::vector<x3::forward_ast<AssignmentExpression>>;
using PrimaryExpression =
    x3::variant<Expression, std::string *, std::string, int>;

struct FunctionApplication {
  PrimaryExpression identifier;
  std::vector<Expression> argument_lists;
};

using PostfixExpression = x3::variant<PrimaryExpression, FunctionApplication>;

enum class UnaryOperators {
  REFERENCE,
  DEREFERENCE,
  POSITIVE,
  NEGATIVE,
  INVERSION
};

struct UnaryExpression {
  std::vector<UnaryOperators> operators;
  PostfixExpression expression;
};

struct Multiplication {
  UnaryExpression lhs;
  x3::forward_ast<MultiplicativeExpression> rhs;
};

struct Division {
  UnaryExpression lhs;
  x3::forward_ast<MultiplicativeExpression> rhs;
};

struct Modulo {
  UnaryExpression lhs;
  x3::forward_ast<MultiplicativeExpression> rhs;
};

struct MultiplicativeExpression
    : x3::variant<UnaryExpression, Multiplication, Division, Modulo> {
  using base_type::base_type;
  using base_type::operator=;
};

struct Addition {
  MultiplicativeExpression lhs;
  x3::forward_ast<AdditiveExpression> rhs;
};

struct Subtraction {
  MultiplicativeExpression lhs;
  x3::forward_ast<AdditiveExpression> rhs;
};

struct AdditiveExpression
    : x3::variant<MultiplicativeExpression, Addition, Subtraction> {
  using base_type::base_type;
  using base_type::operator=;
};

struct LessThan {
  AdditiveExpression lhs;
  x3::forward_ast<RelationalExpression> rhs;
};

struct GreaterThan {
  AdditiveExpression lhs;
  x3::forward_ast<RelationalExpression> rhs;
};

struct LessThanOrEqualTo {
  AdditiveExpression lhs;
  x3::forward_ast<RelationalExpression> rhs;
};

struct GreaterThanOrEqualTo {
  AdditiveExpression lhs;
  x3::forward_ast<RelationalExpression> rhs;
};

struct RelationalExpression
    : x3::variant<AdditiveExpression, LessThan, GreaterThan, LessThanOrEqualTo,
                  GreaterThanOrEqualTo> {
  using base_type::base_type;
  using base_type::operator=;
};

struct Equals {
  RelationalExpression lhs;
  x3::forward_ast<EqualityExpression> rhs;
};

struct NotEqual {
  RelationalExpression lhs;
  x3::forward_ast<EqualityExpression> rhs;
};

struct EqualityExpression
    : x3::variant<RelationalExpression, Equals, NotEqual> {
  using base_type::base_type;
  using base_type::operator=;
};

struct Assignment {
  UnaryExpression lhs;
  x3::forward_ast<AssignmentExpression> rhs;
};

struct AssignmentExpression : x3::variant<EqualityExpression, Assignment> {
  using base_type::base_type;
  using base_type::operator=;
};

} // namespace AST
} // namespace Parser

#endif
