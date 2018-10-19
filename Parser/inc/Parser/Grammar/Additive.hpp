#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/auxiliary.hpp>

#include "Parser/AST/Expression.hpp"

#include "Parser/Grammar/Keywords.hpp"
#include "Parser/Grammar/Rules.hpp"

#include <boost/bind.hpp>

namespace {

using namespace Parser::AST;

struct AdditiveHelper {
  MultiplicativeExpression multiplicative;
  char op;
  AdditiveExpression additive;
};

AdditiveExpression get_additive(MultiplicativeExpression expression,
                                AdditiveExpression additive, char op) {
  switch (op) {
  case '+':
    return AdditiveExpression(
        Addition{std::move(expression), std::move(additive)});
  default:
    return AdditiveExpression(
        Subtraction{std::move(expression), std::move(additive)});
  }
}

AdditiveExpression get_additive(AdditiveHelper const &helper) {
  return get_additive(helper.multiplicative, helper.additive, helper.op);
}

auto create_additive() {
  return [](auto const &context) {
    x3::_val(context) = get_additive(std::move(x3::_attr(context)));
  };
}

auto multiplicative_to_additive() {
  return [](auto const &context) {
    x3::_val(context) = AdditiveExpression(std::move(x3::_attr(context)));
  };
}
} // namespace

BOOST_FUSION_ADAPT_STRUCT(AdditiveHelper, multiplicative, op, additive)

namespace Parser {
namespace Grammar {

namespace x3 = boost::spirit::x3;

auto const additive_helper = x3::rule<struct _, AdditiveHelper>{} =
    multiplicative_expression >>
    (x3::char_('+') | x3::char_('-')) >> additive_expression;

auto const additive_expression_def =
    additive_helper[create_additive()] |
    multiplicative_expression[multiplicative_to_additive()];

} // namespace Grammar
} // namespace Parser
