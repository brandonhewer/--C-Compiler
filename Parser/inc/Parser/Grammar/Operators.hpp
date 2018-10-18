#ifndef __OPERATORS_HPP_
#define __OPERATORS_HPP_

#include <boost/spirit/home/x3.hpp>

using boost::spirit::x3::lit;

namespace Parser {
namespace Grammar {

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

}
}

#endif
