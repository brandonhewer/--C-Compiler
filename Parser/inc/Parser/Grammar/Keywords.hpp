#ifndef __KEYWORDS_HPP_
#define __KEYWORDS_HPP_

#include <boost/spirit/home/x3.hpp>

using boost::spirit::x3::lit;

namespace x3 = boost::spirit::x3;

namespace Parser {
namespace Grammar {

// Minus2C keywords
struct keywords : x3::symbols<> {
  keywords() {
    add("auto");
    add("break");
    add("continue");
    add("else");
    add("extern");
    add("function");
    add("if");
    add("int");
    add("return");
    add("void");
    add("while");
  }
} keywords;

// Minus2C operators
auto const LEFT_BRACE = '{' | lit("<%");
auto const RIGHT_BRACE = '}' | lit("%>");
auto const LEFT_BRACKET = '[' | lit("<:");
auto const RIGHT_BRACKET = ']' | lit(":>");

// Tokens
auto const AUTO = lit("auto");
auto const BREAK = lit("break");
auto const CONTINUE = lit("continue");
auto const ELSE = lit("else");
auto const EXTERN = lit("extern");
auto const FUNCTION = lit("function");
auto const IF = lit("if");
auto const INT = lit("int");
auto const RETURN = lit("return");
auto const VOID = lit("void");
auto const WHILE = lit("while");

// Operators
auto const OR_OP = lit("||");
auto const LE_OP = lit("<=");
auto const GE_OP = lit(">=");
auto const EQ_OP = lit("==");
auto const NE_OP = lit("!=");
auto const SEMICOLON = lit(';');
auto const COMMA = lit(',');
auto const ASSIGN = lit('=');
auto const LEFT_PAREN = lit('(');
auto const RIGHT_PAREN = lit(')');
auto const ADDROF = lit('&');
auto const BANG = lit('!');
auto const MINUS = lit('-');
auto const PLUS = lit('+');
auto const STAR = lit('*');
auto const SLASH = lit('/');
auto const PERCENT = lit('%');
auto const LT_OP = lit('<');
auto const GT_OP = lit('>');

} // namespace Grammar
} // namespace Parser

#endif
