#include "Interpreter/ANormalForm/Printers.hpp"

#include <boost/algorithm/string/join.hpp>

#include <functional>
#include <sstream>
#include <variant>

namespace {

using namespace Interpreter::ANormalForm;
using namespace Parser::AST;

constexpr std::size_t INDENT = 2;

std::string operator_to_string(Parser::AST::UnaryOperators op) {
  switch (op) {
  case UnaryOperators::REFERENCE:
    return "&";
  case UnaryOperators::DEREFERENCE:
    return "*";
  case UnaryOperators::POSITIVE:
    return "";
  case UnaryOperators::NEGATIVE:
    return "-";
  case UnaryOperators::INVERSION:
    return "!";
  }
}

std::string operator_to_string(BinaryOperators op) {
  switch (op) {
  case BinaryOperators::ADDITION:
    return "+";
  case BinaryOperators::SUBTRACTION:
    return "-";
  case BinaryOperators::MULTIPLICATION:
    return "*";
  case BinaryOperators::DIVISION:
    return "/";
  case BinaryOperators::MODULO:
    return "%";
  case BinaryOperators::LESS_THAN:
    return "<";
  case BinaryOperators::GREATER_THAN:
    return ">";
  case BinaryOperators::LESS_THAN_OR_EQUAL_TO:
    return "<=";
  case BinaryOperators::GREATER_THAN_OR_EQUAL_TO:
    return ">=";
  case BinaryOperators::EQUALS:
    return "==";
  case BinaryOperators::NOT_EQUAL:
    return "!=";
  }
}

std::string
storage_class_to_string(StorageClassSpecifier const &storage_class) {
  switch (storage_class) {
  case StorageClassSpecifier::AUTO:
    return "";
  case StorageClassSpecifier::EXTERN:
    return "extern";
  }
}

std::string type_to_string(TypeSpecifier const &type) {
  switch (type) {
  case TypeSpecifier::INT:
    return "int";
  case TypeSpecifier::FUNCTION:
    return "function";
  case TypeSpecifier::VOID:
    return "void";
  }
}

std::string jump_to_string(JumpKeywords const &jump_keyword) {
  switch (jump_keyword) {
  case JumpKeywords::BREAK:
    return "break";
  case JumpKeywords::CONTINUE:
    return "continue";
  }
}

std::string temporary_to_string(TemporaryAssignment const *assignment) {
  std::ostringstream address;
  address << (void const *)assignment;
  std::string address_string = address.str();
  return "free_" + address_string;
}

struct OperandToString {

  std::string operator()(std::string *identifier) const {
    if (nullptr != identifier)
      return *identifier;
    return "";
  }

  std::string operator()(TemporaryAssignment const *assignment) const {
    return temporary_to_string(assignment);
  }

  std::string operator()(int constant) const {
    return std::to_string(constant);
  }
};

std::string operand_to_string(Operand const &operand) {
  return std::visit(OperandToString(), operand);
}

std::string unary_operation_to_string(UnaryOperation const &op) {
  return operator_to_string(op.op) + operand_to_string(op.operand);
}

std::string binary_operation_to_string(BinaryOperation const &op) {
  return operand_to_string(op.lhs) + " " + operator_to_string(op.op) + " " +
         operand_to_string(op.rhs);
}

struct FunctionIdentifierToString {

  std::string operator()(std::string *identifier) const {
    if (nullptr == identifier)
      return "";
    return *identifier;
  }

  std::string operator()(TemporaryAssignment const *assignment) const {
    return temporary_to_string(assignment);
  }
};

std::string function_identifier_to_string(
    std::variant<std::string *, TemporaryAssignment const *> const
        &function_identifier) {
  return std::visit(FunctionIdentifierToString(), function_identifier);
}

std::string function_argument_to_string(Operand const &argument) {
  return operand_to_string(argument);
}

std::string
function_arguments_to_string(std::vector<Operand> const &arguments) {
  std::vector<std::string> operand_strings;
  operand_strings.reserve(arguments.size());
  std::transform(arguments.begin(), arguments.end(),
                 std::back_inserter(operand_strings),
                 function_argument_to_string);
  return boost::algorithm::join(operand_strings, ",");
}

std::string function_call_to_string(FunctionCall const &function_call) {
  return function_identifier_to_string(function_call.function_identifier) +
         " (" + function_arguments_to_string(function_call.operands) + ")";
}

struct OperationToString {

  std::string operator()(Operand const &operand) const {
    return operand_to_string(operand);
  }

  std::string operator()(UnaryOperation const &op) const {
    return unary_operation_to_string(op);
  }

  std::string operator()(BinaryOperation const &op) const {
    return binary_operation_to_string(op);
  }

  std::string operator()(FunctionCall const &function_call) const {
    return function_call_to_string(function_call);
  }
};

std::string operation_to_string(Operation const &operation) {
  return std::visit(OperationToString(), operation);
}

std::string
temporary_assignment_to_string(TemporaryAssignment const &assignment) {
  return temporary_to_string(&assignment) + " = " +
         operation_to_string(assignment.expression);
}

std::string
variable_assignment_to_string(VariableAssignment const &assignment) {
  return *assignment.variable + " = " +
         operation_to_string(assignment.expression);
}

std::string
variable_declaration_to_string(VariableDeclaration const &declaration) {
  auto const storage_class = storage_class_to_string(declaration.storage_class);
  auto const type = type_to_string(declaration.type);

  if (storage_class.empty())
    return "declare " + type + " " + *declaration.name;
  return "declare " + storage_class + " " + type + " " + *declaration.name;
}

std::string function_parameter_to_string(VariableDeclaration const &parameter) {
  auto const storage_class = storage_class_to_string(parameter.storage_class);
  auto const type = type_to_string(parameter.type);

  if (storage_class.empty())
    return type + " " + *parameter.name;
  return storage_class + " " + type + " " + *parameter.name;
}

std::string function_parameters_to_string(
    std::vector<VariableDeclaration> const &parameters) {
  std::vector<std::string> parameter_strings;
  parameter_strings.reserve(parameters.size());
  std::transform(parameters.begin(), parameters.end(),
                 std::back_inserter(parameter_strings),
                 function_parameter_to_string);
  return boost::algorithm::join(parameter_strings, ",");
}

std::string
function_declaration_to_string(FunctionDeclaration const &declaration) {
  auto const suffix = *declaration.name + " (" +
                      function_parameters_to_string(declaration.declarations) +
                      ")";
  auto const storage_class = storage_class_to_string(declaration.storage_class);
  auto const type = type_to_string(declaration.type);

  if (storage_class.empty())
    return "declare " + type + " " + suffix;
  return "declare " + storage_class + " " + type + " " + suffix;
}

std::string return_to_string(NormalReturn const &return_statement) {
  if (auto return_value = return_statement.value)
    return "return " + operand_to_string(*return_value);
  return "return";
}

std::string compound_statement_to_string(NormalCompoundStatement const &,
                                         std::size_t);

std::string if_to_string(NormalIf const &if_statement, std::size_t indents) {
  auto const condition =
      "if (" + operand_to_string(if_statement.condition) + ")";
  auto const indentation = std::string(INDENT * indents, ' ');
  return condition + " {\n" +
         compound_statement_to_string(*if_statement.body, indents + 1) + "\n" +
         indentation + "}";
}

std::string if_else_to_string(NormalIfElse const &if_else,
                              std::size_t indents) {
  auto const if_string = if_to_string(if_else.if_statement, indents);
  return if_string + "\nelse\n" +
         compound_statement_to_string(*if_else.else_body, indents + 1);
}

std::string while_to_string(NormalWhile const &while_statement,
                            std::size_t indents) {
  auto const condition =
      "while (" + operand_to_string(while_statement.condition) + ")";
  return condition + "\n" +
         compound_statement_to_string(*while_statement.body, indents + 1);
}

std::string
function_definition_header_to_string(FunctionDeclaration const &header) {
  auto const suffix = *header.name + " (" +
                      function_parameters_to_string(header.declarations) + ")";
  auto const storage_class = storage_class_to_string(header.storage_class);
  auto const type = type_to_string(header.type);

  if (storage_class.empty())
    return type + " " + suffix;
  return storage_class + " " + type + " " + suffix;
}

std::string function_definition_to_string(
    NormalFunctionDefinition const &function_definition, std::size_t indents) {
  auto const header =
      function_definition_header_to_string(function_definition.declaration);

  if (function_definition.body->statements.empty())
    return header + " {}";

  auto const indentation = std::string(INDENT * indents, ' ');
  return function_definition_header_to_string(function_definition.declaration) +
         " {\n" +
         compound_statement_to_string(*function_definition.body, indents + 1) +
         "\n" + indentation + "}";
}

struct NormalStatementToString {
  NormalStatementToString(std::size_t indents)
      : m_indents(indents), m_prefix(std::string(indents * INDENT, ' ')) {}

  std::string operator()(NormalIf const &if_statement) const {
    return m_prefix + if_to_string(if_statement, m_indents);
  }

  std::string operator()(NormalIfElse const &if_else_statement) const {
    return m_prefix + if_else_to_string(if_else_statement, m_indents);
  }

  std::string operator()(NormalWhile const &while_statement) const {
    return m_prefix + while_to_string(while_statement, m_indents);
  }

  std::string operator()(NormalReturn const &return_statement) const {
    return m_prefix + return_to_string(return_statement);
  }

  std::string operator()(JumpKeywords const &jump_keyword) const {
    return m_prefix + jump_to_string(jump_keyword);
  }

  std::string operator()(VariableAssignment const &assignment) const {
    return m_prefix + variable_assignment_to_string(assignment);
  }

  std::string
  operator()(std::unique_ptr<TemporaryAssignment> const &assignment) const {
    return m_prefix + temporary_assignment_to_string(*assignment);
  }

  std::string operator()(VariableDeclaration const &declaration) const {
    return m_prefix + variable_declaration_to_string(declaration);
  }

  std::string operator()(FunctionDeclaration const &declaration) const {
    return m_prefix + function_declaration_to_string(declaration);
  }

  std::string operator()(NormalFunctionDefinition const &definition) const {
    return m_prefix + function_definition_to_string(definition, m_indents);
  }

  std::string
  operator()(std::unique_ptr<NormalCompoundStatement> const &statement) const {
    return m_prefix + "{\n" +
           compound_statement_to_string(*statement, m_indents + 1) + "\n" +
           m_prefix + "}";
  }

private:
  std::string const m_prefix;
  std::size_t m_indents;
};

struct StatementStringCreator {
  StatementStringCreator(std::size_t indents)
      : m_statement_to_string(indents) {}

  std::string operator()(NormalStatement const &statement) const {
    return std::visit(m_statement_to_string, statement);
  }

private:
  NormalStatementToString const m_statement_to_string;
};

std::string statement_to_string(NormalStatement const &statement,
                                std::size_t indents) {
  return std::visit(NormalStatementToString(indents), statement);
}

std::string
compound_statement_to_string(NormalCompoundStatement const &compound_statement,
                             std::size_t indents) {
  StatementStringCreator create_statement_string(indents);
  std::vector<std::string> statement_strings;
  statement_strings.reserve(compound_statement.statements.size());
  std::transform(compound_statement.statements.begin(),
                 compound_statement.statements.end(),
                 std::back_inserter(statement_strings),
                 create_statement_string);
  return boost::algorithm::join(statement_strings, "\n");
}

std::string statements_to_string(std::vector<NormalStatement> const &statements,
                                 std::size_t indents) {
  StatementStringCreator create_statement_string(indents);
  std::vector<std::string> statement_strings;
  statement_strings.reserve(statements.size());
  std::transform(statements.begin(), statements.end(),
                 std::back_inserter(statement_strings),
                 create_statement_string);
  return boost::algorithm::join(statement_strings, "\n");
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

std::ostream &operator<<(std::ostream &output_stream,
                         VariableAssignment const &assignment) {
  output_stream << variable_assignment_to_string(assignment);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         TemporaryAssignment const &assignment) {
  output_stream << temporary_assignment_to_string(assignment);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         VariableDeclaration const &declaration) {
  output_stream << variable_declaration_to_string(declaration);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         FunctionDeclaration const &declaration) {
  output_stream << function_declaration_to_string(declaration);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalReturn const &normal_return) {
  output_stream << return_to_string(normal_return);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalIf const &if_statement) {
  output_stream << if_to_string(if_statement, 0);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalIfElse const &if_else_statement) {
  output_stream << if_else_to_string(if_else_statement, 0);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalWhile const &while_statement) {
  output_stream << while_to_string(while_statement, 0);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalFunctionDefinition const &function_definition) {
  output_stream << function_definition_to_string(function_definition, 0);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalStatement const &statement) {
  output_stream << statement_to_string(statement, 0);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         NormalCompoundStatement const &statement) {
  output_stream << compound_statement_to_string(statement, 0);
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         std::vector<NormalStatement> const &statements) {
  output_stream << statements_to_string(statements, 0);
  return output_stream;
}

} // namespace ANormalForm
} // namespace Interpreter
