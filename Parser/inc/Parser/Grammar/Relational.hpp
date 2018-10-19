#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/auxiliary.hpp>

#include "Parser/AST/Expression.hpp"

#include "Parser/Grammar/Keywords.hpp"
#include "Parser/Grammar/Rules.hpp"

#include <boost/bind.hpp>

namespace {

using namespace Parser::AST;

enum class Relation { LT, LTE, GT, GTE };

struct RelationalHelper {
  AdditiveExpression additive;
  Relation op;
  RelationalExpression relational;
};

RelationalExpression get_relational(AdditiveExpression expression,
                                    RelationalExpression relational,
                                    Relation op) {
  switch (op) {
  case Relation::LT:
    return RelationalExpression(
        LessThan{std::move(expression), std::move(relational)});
  case Relation::LTE:
    return RelationalExpression(
        LessThanOrEqualTo{std::move(expression), std::move(relational)});
  case Relation::GT:
    return RelationalExpression(
        GreaterThan{std::move(expression), std::move(relational)});
  case Relation::GTE:
    return RelationalExpression(
        GreaterThanOrEqualTo{std::move(expression), std::move(relational)});
  }
}

RelationalExpression get_relational(RelationalHelper const &helper) {
  return get_relational(helper.additive, helper.relational, helper.op);
}

auto create_relational() {
  return [](auto const &context) {
    x3::_val(context) = get_relational(std::move(x3::_attr(context)));
  };
}

auto additive_to_relational() {
  return [](auto const &context) {
    x3::_val(context) = RelationalExpression(std::move(x3::_attr(context)));
  };
}
} // namespace

BOOST_FUSION_ADAPT_STRUCT(RelationalHelper, additive, op, relational)

namespace Parser {
namespace Grammar {

namespace x3 = boost::spirit::x3;

auto const lt_relation = LT_OP >> x3::attr(Relation::LT);
auto const gt_relation = GT_OP >> x3::attr(Relation::GT);
auto const lte_relation = LE_OP >> x3::attr(Relation::LTE);
auto const gte_relation = GE_OP >> x3::attr(Relation::GTE);

auto const relation = lt_relation | gt_relation | lte_relation | gte_relation;
auto const relational_helper = x3::rule<struct _, RelationalHelper>{} =
    additive_expression >> relation >> relational_expression;

auto const relational_expression_def =
    relational_helper[create_relational()] |
    additive_expression[additive_to_relational()];

} // namespace Grammar
} // namespace Parser
