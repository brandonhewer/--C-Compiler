#ifndef __STRING_LITERAL_HPP_
#define __STRING_LITERAL_HPP_

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace Parser {
namespace Grammar {

x3::rule<class string_literal, std::string> STRING_LITERAL("string_literal");

// String literals
auto const STRING_LITERAL_PART =
    x3::lexeme['L' >> x3::lit('\"') >> *(x3::lit("\\\"")) |
               (x3::char_ - '\"') >> '\"'];

auto const STRING_LITERAL_def = +STRING_LITERAL_PART;

BOOST_SPIRIT_DEFINE(STRING_LITERAL);

} // namespace Grammar
} // namespace Parser

#endif
