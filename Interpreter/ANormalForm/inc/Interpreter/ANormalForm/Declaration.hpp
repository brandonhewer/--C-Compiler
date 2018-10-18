#ifndef __DECLARATION_HPP_
#define __DECLARATION_HPP_

#include "Interpreter/ANormalForm/Expression.hpp"
#include "Parser/AST/Declaration.hpp"

#include <memory>
#include <variant>

namespace Interpreter {
namespace ANormalForm {

struct VariableDeclaration {
  std::string *name;
  Parser::AST::StorageClassSpecifier storage_class;
  Parser::AST::TypeSpecifier type;
};

struct FunctionDeclaration {
  std::string *name;
  Parser::AST::StorageClassSpecifier storage_class;
  Parser::AST::TypeSpecifier type;
  std::vector<VariableDeclaration> declarations;
};

} // namespace ANormalForm
} // namespace Interpreter

#endif
