#ifndef __PARSE_H
#define __PARSE_H

#include "Parser/Grammar/Grammar.hpp"

namespace {

using namespace Parser::AST;

template <typename StartIt, typename EndIt, typename Parser, typename Skipper>
TranslationUnit
parse_minus2c_with_skipper(Parser const &parser, Skipper const &skipper,
                           StartIt start_iterator, EndIt end_iterator) {
  TranslationUnit ast;
  bool parsed =
      phrase_parse(start_iterator, end_iterator, parser, skipper, ast);

  if (!parsed)
    throw std::runtime_error("Parsing failed (Unknown failure).");
  else if (start_iterator != end_iterator)
    throw std::runtime_error("Parsing failed (Incomplete parse).");
  return ast;
}

} // namespace

namespace Parser {

using namespace boost::spirit::x3;

template <typename StartIt, typename EndIt>
AST::TranslationUnit
parse_minus2c(StartIt start_iterator, EndIt end_iterator,
              std::unordered_map<std::string, std::string> &symbols) {
  auto const parser = with<Grammar::symbol_map_tag>(
      std::ref(symbols))[Grammar::translation_unit];
  auto const skipper = ("/*" >> *(char_ - "*/") >> "*/") | ascii::space;
  return parse_minus2c_with_skipper(parser, skipper, start_iterator,
                                    end_iterator);
}

} // namespace Parser

#endif
