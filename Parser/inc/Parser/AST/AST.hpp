#ifndef __ASTNODE_H
#define __ASTNODE_H

#include "Parser/AST/Statement.hpp"

namespace Parser {
namespace AST {

struct FunctionDefinition {
  std::vector<DeclarationSpecifier> specifiers;
  FunctionDeclarator declarator;
  CompoundStatement body;
};

using ExternalDeclaration = x3::variant<FunctionDefinition, Declaration>;
using TranslationUnit = std::vector<ExternalDeclaration>;

} // namespace AST
} // namespace Parser

#endif
