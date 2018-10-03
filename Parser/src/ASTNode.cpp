#include "Parser/ASTNode.hpp"
#include "Parser/C.tab.h"

#include <stdio.h>
#include <stdlib.h>

namespace Parser {

ASTNode::ASTNode(Token const &_value) : value(_value) {}

ASTNode::ASTNode(Token const &_value, std::unique_ptr<ASTNode> _left,
                 std::unique_ptr<ASTNode> _right)
    : value(_value), left(std::move(_left)), right(std::move(_right)) {}

} // namespace Parser
