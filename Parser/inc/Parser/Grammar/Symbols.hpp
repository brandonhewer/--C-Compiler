#ifndef __SYMBOLS_HPP_
#define __SYMBOLS_HPP_

#include <boost/spirit/home/x3.hpp>

#include "Parser/AST/ASTAdapted.hpp"
#include "Parser/Grammar/Keywords.hpp"

namespace x3 = boost::spirit::x3;

namespace Parser {
namespace Grammar {

struct unary_operator : x3::symbols<AST::UnaryOperators> {
  unary_operator() {
    add("&", AST::UnaryOperators::REFERENCE)
       ("*", AST::UnaryOperators::DEREFERENCE)
       ("+", AST::UnaryOperators::POSITIVE)
       ("-", AST::UnaryOperators::NEGATIVE)
       ("!", AST::UnaryOperators::INVERSION);
  }
} unary_operator;

struct type_specifier : x3::symbols<AST::TypeSpecifier> {
  type_specifier() {
    add("void",     AST::TypeSpecifier::VOID)
       ("function", AST::TypeSpecifier::FUNCTION)
       ("int",      AST::TypeSpecifier::INT);
  }
} type_specifier;

struct storage_class_specifier : x3::symbols<AST::StorageClassSpecifier> {
  storage_class_specifier() {
    add("extern", AST::StorageClassSpecifier::EXTERN)
       ("auto",   AST::StorageClassSpecifier::AUTO);
  }
} storage_class_specifier;

struct jump_keywords : x3::symbols<AST::JumpKeywords> {
  jump_keywords() {
    add("continue", AST::JumpKeywords::CONTINUE)
       ("break",    AST::JumpKeywords::BREAK);
  }
} jump_keywords;

}
}

#endif
