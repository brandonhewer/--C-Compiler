#ifndef __ASTNODE_H
#define __ASTNODE_H

#include "Parser/Token.hpp"

#include <memory>

namespace Parser {

struct ASTNode {
  explicit ASTNode(Token const &_value);
  ASTNode(Token const &_value, std::unique_ptr<ASTNode> _left,
          std::unique_ptr<ASTNode> _right);

  Token value;
  std::unique_ptr<ASTNode> left;
  std::unique_ptr<ASTNode> right;
};

std::unique_ptr<ASTNode> make_node(Token const &);
std::unique_ptr<ASTNode> make_node(Token const &, std::unique_ptr<ASTNode>,
                                   std::unique_ptr<ASTNode>);

} // namespace Parser

#endif
