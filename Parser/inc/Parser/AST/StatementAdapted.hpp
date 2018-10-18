#ifndef __STATEMENT_ADAPTED_H
#define __STATEMENT_ADAPTED_H

#include "Parser/AST/Statement.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::If, condition, body)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::IfElse, if_statement, else_body)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::While, condition, body)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Return, expression)

#endif