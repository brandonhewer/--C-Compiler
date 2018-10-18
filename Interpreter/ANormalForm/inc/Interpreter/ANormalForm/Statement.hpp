#ifndef __STATEMENT_HPP_
#define __STATEMENT_HPP_

#include "Interpreter/ANormalForm/Declaration.hpp"
#include "Parser/AST/Statement.hpp"

#include <optional>

namespace Interpreter {
namespace ANormalForm {

struct NormalCompoundStatement;

struct NormalIf {
  Operand condition;
  std::unique_ptr<NormalCompoundStatement> body;
};

struct NormalIfElse {
  NormalIf if_statement;
  std::unique_ptr<NormalCompoundStatement> else_body;
};

struct NormalWhile {
  Operand condition;
  std::unique_ptr<NormalCompoundStatement> body;
};

struct NormalReturn {
  std::optional<Operand> value;
};

struct NormalFunctionDefinition {
  FunctionDeclaration declaration;
  std::unique_ptr<NormalCompoundStatement> body;
};

using NormalStatement =
    std::variant<NormalIf, NormalIfElse, NormalWhile, NormalReturn,
                 Parser::AST::JumpKeywords, VariableAssignment,
                 TemporaryAssignment, VariableDeclaration, FunctionDeclaration,
                 NormalFunctionDefinition,
                 std::unique_ptr<NormalCompoundStatement>>;

struct NormalCompoundStatement {
  std::vector<NormalStatement> statements;
};

} // namespace ANormalForm
} // namespace Interpreter

#endif
