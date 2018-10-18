#ifndef __EXPRESSION_ADAPTED_H
#define __EXPRESSION_ADAPTED_H

#include "Parser/AST/Expression.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::FunctionApplication, identifier,
                          argument_lists)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::UnaryExpression, operators, expression)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Multiplication, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Division, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Modulo, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Addition, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Subtraction, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::LessThan, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::GreaterThan, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::LessThanOrEqualTo, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::GreaterThanOrEqualTo, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Equals, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::NotEqual, lhs, rhs)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Assignment, lhs, rhs)

#endif