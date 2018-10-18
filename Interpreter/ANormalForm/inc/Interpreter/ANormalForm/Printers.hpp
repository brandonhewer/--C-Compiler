#ifndef __ANORMALFORMPRINTERS_HPP_
#define __ANORMALFORMPRINTERS_HPP_

#include "Interpreter/ANormalForm/Statement.hpp"

namespace Interpreter {
namespace ANormalForm {

std::ostream &operator<<(std::ostream &output_stream,
                         VariableAssignment const &assignment);

std::ostream &operator<<(std::ostream &output_stream,
                         TemporaryAssignment const &assignment);

std::ostream &operator<<(std::ostream &output_stream,
                         VariableDeclaration const &declaration);

std::ostream &operator<<(std::ostream &output_stream,
                         FunctionDeclaration const &declaration);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalReturn const &normal_return);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalIf const &if_statement);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalIfElse const &if_else_statement);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalWhile const &while_statement);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalFunctionDefinition const &function_definition);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalStatement const &statement);

std::ostream &operator<<(std::ostream &output_stream,
                         NormalCompoundStatement const &statement);

std::ostream &operator<<(std::ostream &output_stream,
                         std::vector<NormalStatement> const &statements);

} // namespace ANormalForm
} // namespace Interpreter

#endif
