#include "AbstractSyntaxTree.hpp"

namespace {
using namespace Parser::AST;
using namespace boost::spirit::x3;

struct symbol_adder {
  symbol_adder(std::unordered_map<std::string, std::string> &symbols)
      : m_symbols(symbols) {}

  void operator()(Context &context) {
    auto const symbol = _attr(context);
    if (symbols.end() != symbols.find(symbol))
      symbols[symbol] = symbol;
  }

private:
  std::unordered_map<std::string, std::string> &m_symbols;
};

auto create_grammar(std::unordered_map<std::string, std::string> &symbols) {
  rule<class expression, Expression> expression("expression");
  rule<class primary_expression, PrimaryExpression> primary_expression(
      "primary_expression");
  rule<class postfix_expression, PostfixExpression> postfix_expression(
      "postfix_expression");
  rule<class assignment_expression, AssignmentExpression> assignment_expression(
      "assignment_expression");
  rule<class unary_expression, UnaryExpression> unary_expression(
      "unary_expression");
  rule<class multiplicative_expression, MultiplicativeExpression>
      multiplicative_expression("multiplicative_expression");
  rule<class additive_expression, AdditiveExpression> additive_expression(
      "additive_expression");
  rule<class relational_expression, RelationalExpression> relational_expression(
      "relational_expression");
  rule<class equality_expression, EqualityExpression> equality_expression(
      "equality_expression");
  rule<class parameter_declaration, ParameterDeclaration> parameter_declaration(
      "parameter_declaration");

  auto const string_literal = lexeme['"' >> *(char_ - '"') >> '"'];
  auto const identifier =
      *(alpha | char_('_')) >> *(alnum | char_('_'))[symbol_adder(symbols)];
  auto const primary_expression_def = string_literal | identifier | int_;

  auto const assignment_expressions =
      *('(' >> assignment_expression % ',' >> ')');
  auto const postfix_expression_def =
      primary_expression >> assignment_expressions;

  auto const reference = '&' >> attr(UnaryOperators::REFERENCE);
  auto const dereference = '*' >> attr(UnaryOperators::DEREFERENCE);
  auto const plus = '+' >> attr(UnaryOperators::POSITIVE);
  auto const negative = '-' >> attr(UnaryOperators::NEGATIVE);
  auto const inversion = '!' >> attr(UnaryOperators::INVERSION);
  auto const unary_operators =
      reference | dereference | plus | negative | inversion;
  auto const unary_expression_def = *(unary_operators) >> postfix_expression;

  auto const multiplication =
      multiplicative_expression >> '*' >> unary_expression;
  auto const division = multiplicative_expression >> '/' >> unary_expression;
  auto const modulo = multiplicative_expression >> '%' >> unary_expression;
  auto const multiplicative_expression_def =
      unary_expression | multiplication | division | modulo;

  auto const addition = additive_expression >> '+' >> multiplicative_expression;
  auto const subtraction =
      additive_expression >> '-' >> multiplicative_expression;
  auto const additive_expression_def =
      multiplicative_expression | addition | subtraction;

  auto const less_than = relational_expression >> '<' >> additive_expression;
  auto const greater_than = relational_expression >> '>' >> additive_expression;
  auto const less_than_or_equal_to =
      relational_expression >> "<=" >> additive_expression;
  auto const greater_than_or_equal_to =
      relational_expression >> ">=" >> additive_expression;
  auto const relational_expression_def = additive_expression | less_than |
                                         greater_than | less_than_or_equal_to |
                                         greater_than_or_equal_to;

  auto const equals = equality_expression >> "==" >> relational_expression;
  auto const not_equal = equality_expression >> "!=" >> relational_expression;
  auto const equality_expression_def =
      relational_expression | equals | not_equal;

  auto const assignment = unary_expression >> '=' >> assignment_expression;
  auto const assignment_expression_def = assignment | equality_expression;

  auto const auto_specifier = "auto" >> attr(StorageClassSpecifier::AUTO);
  auto const extern_specifier = "extern" >> attr(StorageClassSpecifier::EXTERN);
  auto const void_specifier = "void" >> attr(TypeSpecifier::VOID);
  auto const int_specifier = "int" >> attr(TypeSpecifier::INT);
  auto const function_specifier = "function" >> attr(TypeSpecifier::FUNCTION);
  auto const type_specifier =
      void_specifier | int_specifier | function_specifier;
  auto const declaration_specifier =
      type_specifier | auto_specifier | extern_specifier;

  auto const parameters = *(parameter_declaration);
  return declaration_specifier;
}
} // namespace

namespace Parser {
namespace Grammar {


} // namespace Grammar
} // namespace Parser
