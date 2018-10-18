#ifndef __IDENTIFIER_HPP_
#define __IDENTIFIER_HPP_

#include "Parser/Grammar/Keywords.hpp"

#include <boost/spirit/home/x3.hpp>

#include <string>
#include <unordered_map>

namespace x3 = boost::spirit::x3;

using boost::spirit::x3::alnum;
using boost::spirit::x3::alpha;
using boost::spirit::x3::char_;
using boost::spirit::x3::lexeme;

namespace Parser {
namespace Grammar {

struct symbol_map_tag {};

std::string *get_pointer(std::string &value) { return &value; }

template <typename T, typename... Ts>
T *find_or_insert_symbol(std::unordered_map<T, T, Ts...> &symbols,
                         T const &symbol) {
  auto symbolIt = symbols.find(symbol);
  if (symbols.end() == symbolIt)
    return get_pointer(symbols[symbol] = symbol);
  return get_pointer(symbolIt->second);
}

auto symbol_lookup() {
  return [](auto const &context) {
    auto &symbols = x3::get<symbol_map_tag>(context).get();
    x3::_val(context) = find_or_insert_symbol(symbols, x3::_attr(context));
  };
}

x3::rule<class identifier, std::string *> const IDENTIFIER("identifier");

auto const underscore = char_('_');
auto const dollar = char_('$');
auto const identifier_helper = x3::rule<struct _, std::string>{} =
    lexeme[((alpha | underscore | dollar) >> *(alnum | underscore | dollar)) -
           (keywords >> char_ - (alnum | underscore | dollar))];

auto const IDENTIFIER_def = identifier_helper[symbol_lookup()];

BOOST_SPIRIT_DEFINE(IDENTIFIER)

} // namespace Grammar
} // namespace Parser

#endif
