#ifndef __AST_ADAPTED_H
#define __AST_ADAPTED_H

#include "Parser/AST/AST.hpp"
#include "Parser/AST/DeclarationAdapted.hpp"
#include "Parser/AST/ExpressionAdapted.hpp"
#include "Parser/AST/StatementAdapted.hpp"

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::FunctionDefinition, specifiers,
                          declarator, body)

#endif