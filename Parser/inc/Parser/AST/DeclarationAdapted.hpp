#ifndef __DECLARATION_ADAPTED_H
#define __DECLARATION_ADAPTED_H

#include "Parser/AST/Declaration.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::FunctionDeclarator, identifier,
                          parameters)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::InitDeclarator, declarator, assignment)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::ParameterDeclaration, specifiers,
                          identifier)
BOOST_FUSION_ADAPT_STRUCT(Parser::AST::VariableInitializer, specifiers,
                          declarators)

#endif