#ifndef __STATEMENT_H
#define __STATEMENT_H

#include "Parser/AST/Declaration.hpp"

namespace Parser {
namespace AST {

struct Statement;

struct If {
  Expression condition;
  x3::forward_ast<Statement> body;
};

struct IfElse {
  If if_statement;
  x3::forward_ast<Statement> else_body;
};

struct While {
  Expression condition;
  x3::forward_ast<Statement> body;
};

struct Return {
  Expression expression;
};

enum class JumpKeywords { CONTINUE, BREAK };
using JumpStatement = x3::variant<Return, JumpKeywords>;

using DeclarationOrStatement =
    x3::variant<Declaration, x3::forward_ast<Statement>>;
using CompoundStatement = std::vector<DeclarationOrStatement>;

struct Statement : x3::variant<CompoundStatement, Expression, If, IfElse, While,
                               JumpStatement> {
  using base_type::base_type;
  using base_type::operator=;
};

} // namespace AST
} // namespace Parser

#endif
