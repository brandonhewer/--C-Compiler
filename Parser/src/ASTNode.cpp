#include "Parser/ASTNode.hpp"
#include "Parser/C.tab.h"

#include <stdio.h>
#include <stdlib.h>

namespace Parser {

ASTNode::ASTNode(Token const &_value) : value(_value) {}

ASTNode::ASTNode(Token const &_value, std::unique_ptr<ASTNode> _left,
                 std::unique_ptr<ASTNode> _right) {}

std::unique_ptr<ASTNode> make_node(Token const &token) {
  return std::make_unique<ASTNode>(token);
}

std::unique_ptr<ASTNode> make_node(Token const &token,
                                   std::unique_ptr<ASTNode> left,
                                   std::unique_ptr<ASTNode> right) {
  return std::make_unique<ASTNode>(token, std::move(left), std::move(right));
}

} // namespace Parser
