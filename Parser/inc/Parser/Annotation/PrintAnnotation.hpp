#ifndef __PRINT_ANNOTATION_H_
#define __PRINT_ANNOTATION_H_

#include "Parser/AST/Printers.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

#include <iostream>

namespace Parser {
namespace Grammar {

struct print_annotation {
  print_annotation(std::string const &id) : m_id(id) {}

  template <typename T, typename Iterator, typename Context>
  inline void on_success(Iterator const &first, Iterator const &last, T &ast,
                         Context const &context) {
    using namespace Parser::AST;
    std::cout << "Succeeded in constructing " << m_id << "\n";
    std::cout << "The abstract-syntax-tree representation is now:\n" << ast;
    std::cout << "\n\n" << std::endl;
  }

  template <typename Iterator, typename Exception, typename Context>
  x3::error_handler_result on_error(Iterator &first, Iterator const &last,
                                    Exception const &x,
                                    Context const &context) {
    std::cout << "Error! Failed to construct " + m_id + "." << std::endl;
    return x3::error_handler_result::fail;
  }

private:
  std::string m_id;
};

} // namespace Grammar
} // namespace Parser

#define CREATE_PRINT_ANNOTATOR(name)                                           \
  struct name##_tag : public Parser::Grammar::print_annotation {               \
    name##_tag() : print_annotation(#name) {}                                  \
  };

#define CREATE_PRINT_RULE(rule_name, rule_type) CREATE_PRINT_ANNOTATOR(rule_name) 

#endif
