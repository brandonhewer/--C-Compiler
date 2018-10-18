#ifndef __DECLARATION_H
#define __DECLARATION_H

#include "Parser/AST/Expression.hpp"

#include <boost/optional.hpp>

namespace Parser {
namespace AST {

struct FunctionDefinition;
struct ParameterDeclaration;

enum class StorageClassSpecifier { AUTO, EXTERN };
enum class TypeSpecifier { VOID, INT, FUNCTION };

using DeclarationSpecifier = x3::variant<StorageClassSpecifier, TypeSpecifier>;

struct ParameterDeclaration {
  std::vector<DeclarationSpecifier> specifiers;
  std::string *identifier;
};

using Parameters = std::vector<ParameterDeclaration>;
using Identifiers = std::vector<std::string *>;
using ParametersOrIdentifiers = x3::variant<Parameters, Identifiers>;

struct FunctionDeclarator {
  std::string *identifier;
  ParametersOrIdentifiers parameters;
};

using Declarator = x3::variant<std::string *, FunctionDeclarator>;

struct InitDeclarator {
  Declarator declarator;
  boost::optional<AssignmentExpression> assignment;
};

struct Declaration {
  std::vector<DeclarationSpecifier> specifiers;
  std::vector<InitDeclarator> declarators;
};

} // namespace AST
} // namespace Parser

#endif
