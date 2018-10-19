#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/auxiliary.hpp>

#include "Parser/AST/Expression.hpp"

#include "Parser/Grammar/Keywords.hpp"
#include "Parser/Grammar/Rules.hpp"

#include <boost/bind.hpp>

namespace {

using namespace Parser::AST;

struct MultiplicativeHelper {
  Parser::AST::UnaryExpression unary;
  char op;
  Parser::AST::MultiplicativeExpression multiplicative;
};

MultiplicativeExpression
get_multiplicative(UnaryExpression expression,
                   MultiplicativeExpression multiplicative, char op) {
  switch (op) {
  case '*':
    return MultiplicativeExpression(
        Multiplication{std::move(expression), std::move(multiplicative)});
  case '/':
    return MultiplicativeExpression(
        Division{std::move(expression), std::move(multiplicative)});
  default:
    return MultiplicativeExpression(
        Modulo{std::move(expression), std::move(multiplicative)});
  }
}

MultiplicativeExpression
get_multiplicative(MultiplicativeHelper const &helper) {
  return get_multiplicative(helper.unary, helper.multiplicative, helper.op);
}

auto create_multiplicative() {
  return [](auto const &context) {
    x3::_val(context) = get_multiplicative(std::move(x3::_attr(context)));
  };
}

auto unary_to_multiplicative() {
  return [](auto const &context) {
    x3::_val(context) = MultiplicativeExpression(std::move(x3::_attr(context)));
  };
}

} // namespace

BOOST_FUSION_ADAPT_STRUCT(MultiplicativeHelper, unary, op, multiplicative)

namespace Parser {
namespace Grammar {

namespace x3 = boost::spirit::x3;

auto const multiplicative_helper = x3::rule<struct _, MultiplicativeHelper>{} =
    unary_expression >> (x3::char_('*') | x3::char_('/') | x3::char_('%')) >>
    multiplicative_expression;

auto const multiplicative_expression_def =
    multiplicative_helper[create_multiplicative()] |
    unary_expression[unary_to_multiplicative()];

} // namespace Grammar
} // namespace Parser