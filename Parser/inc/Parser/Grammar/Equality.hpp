#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/auxiliary.hpp>

#include "Parser/AST/Expression.hpp"

#include "Parser/Grammar/Keywords.hpp"
#include "Parser/Grammar/Rules.hpp"

#include <boost/bind.hpp>

namespace {

using namespace Parser::AST;

enum class EqualityOperation { EQ, NEQ };

struct EqualityHelper {
  RelationalExpression relational;
  EqualityOperation op;
  EqualityExpression equality;
};

EqualityExpression get_equality(RelationalExpression expression,
                                EqualityExpression equality,
                                EqualityOperation op) {
  switch (op) {
  case EqualityOperation::EQ:
    return EqualityExpression(
        Equals{std::move(expression), std::move(equality)});
  default:
    return EqualityExpression(
        NotEqual{std::move(expression), std::move(equality)});
  }
}

EqualityExpression get_equality(EqualityHelper const &helper) {
  return get_equality(helper.relational, helper.equality, helper.op);
}

auto create_equality() {
  return [](auto const &context) {
    x3::_val(context) = get_equality(std::move(x3::_attr(context)));
  };
}

auto relational_to_equality() {
  return [](auto const &context) {
    x3::_val(context) = EqualityExpression(std::move(x3::_attr(context)));
  };
}
} // namespace

BOOST_FUSION_ADAPT_STRUCT(EqualityHelper, relational, op, equality)

namespace Parser {
namespace Grammar {

namespace x3 = boost::spirit::x3;

auto const equals = EQ_OP >> x3::attr(EqualityOperation::EQ);
auto const not_equal = NE_OP >> x3::attr(EqualityOperation::NEQ);

auto const equality_helper = x3::rule<struct _, EqualityHelper>{} =
    relational_expression >> (equals | not_equal) >> equality_expression;

auto const equality_expression_def =
    equality_helper[create_equality()] |
    relational_expression[relational_to_equality()];

} // namespace Grammar
} // namespace Parser
