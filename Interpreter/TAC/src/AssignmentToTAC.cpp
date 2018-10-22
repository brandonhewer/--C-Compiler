#include "Interpreter/TAC/AssignmentToTAC.hpp"

namespace {
using namespace Interpreter::ANormalForm;
using namespace Interpreter::TAC;
using namespace Parser::AST;

InstructionOperand get_integer_operand(std::string *identifier,
                                       Environment &environment) {
  auto const &variable = environment.get_integer_variable(identifier);
  if (auto value = variable.variable.value.value)
    return InstructionOperand(*value);
  else if (variable.variable.is_parameter)
    return Parameter{identifier, variable.unique_id};
  else
    return Variable{identifier, variable.unique_id};
}

InstructionOperand get_integer_lvalue(std::string *identifier,
                                      Environment &environment) {
  auto const &variable = environment.get_integer_variable(identifier);
  if (variable.variable.is_parameter)
    return Parameter{identifier, variable.unique_id};
  else
    return Variable{identifier, variable.unique_id};
}

InstructionOperand get_function_operand(std::string *identifier,
                                        Environment &environment) {
  try {
    return ProcedureAddress{environment.get_closure(identifier)};
  } catch (std::out_of_range &) {
    auto variable = environment.get_function_variable(identifier);
    if (auto value = variable.variable.value)
      return ProcedureAddress{value};
    else if (variable.variable.is_parameter)
      return Parameter{identifier, variable.unique_id};
    else
      return Variable{identifier, variable.unique_id};
  }
}

InstructionOperand get_function_lvalue(std::string *identifier,
                                       Environment &environment) {
  try {
    return ProcedureAddress{environment.get_closure(identifier)};
  } catch (std::out_of_range &) {
    auto variable = environment.get_function_variable(identifier);
    if (variable.variable.is_parameter)
      return Parameter{identifier, variable.unique_id};
    else
      return Variable{identifier, variable.unique_id};
  }
}

InstructionOperand get_any_variable(std::string *identifier,
                                    Environment &environment) {
  try {
    return get_integer_operand(identifier, environment);
  } catch (std::out_of_range &) {
    try {
      return get_function_operand(identifier, environment);
    } catch (std::out_of_range &) {
      throw std::runtime_error("no variable exists with the name " +
                               *identifier);
    }
  }
}

struct GetOperandAsRValueWithType {
  GetOperandAsRValueWithType(Environment &environment, Types type)
      : m_environment(environment), m_type(type) {
    if (m_type == Types::VOID)
      throw std::runtime_error("void variable cannot be used as an r-value");
  }

  InstructionOperand operator()(std::string *identifier) const {
    if (m_type == Types::ANY)
      return get_any_variable(identifier, m_environment);
    if (m_type == Types::INT)
      return get_integer_operand(identifier, m_environment);
    else
      return get_function_operand(identifier, m_environment);
  }

  InstructionOperand operator()(TemporaryAssignment const *temporary) const {
    auto const &value = m_environment.temporary_value(temporary);
    if (m_type != Types::ANY && value.type != m_type)
      throw std::runtime_error("invalid type used in expression");
    return Temporary{m_environment.temporary_value(temporary).identifier};
  }

  InstructionOperand operator()(int constant) const {
    if (m_type != Types::INT)
      throw std::runtime_error("function used where integer was expected");
    return InstructionOperand(constant);
  }

private:
  Environment &m_environment;
  Types m_type;
};

struct GetTypeFromOperand {
  GetTypeFromOperand(Environment &environment) : m_environment(environment) {}

  Types operator()(int) const { return Types::INT; }

  Types operator()(TemporaryAssignment const *temporary) const {
    return m_environment.temporary_value(temporary).type;
  }

  Types operator()(std::string *variable) {
    return m_environment.get_variable_type(variable);
  }

private:
  Environment &m_environment;
};

InstructionOperand get_integer_rvalue(Operand const &operand,
                                      Environment &environment) {
  return std::visit(GetOperandAsRValueWithType(environment, Types::INT),
                    operand);
}

InstructionOperand get_function_rvalue(Operand const &operand,
                                       Environment &environment) {
  return std::visit(GetOperandAsRValueWithType(environment, Types::FUNCTION),
                    operand);
}

InstructionOperand get_rvalue(Operand const &operand, Types type,
                              Environment &environment) {
  return std::visit(GetOperandAsRValueWithType(environment, type), operand);
}

Instruction create_negation_instruction(InstructionOperand store,
                                        Operand const &negate,
                                        Environment &environment) {
  return TwoAddressInstruction{TwoAddressOperations::NEGATIVE, std::move(store),
                               get_integer_rvalue(negate, environment)};
}

Instruction create_inversion_instruction(InstructionOperand store,
                                         Operand const &invert,
                                         Environment &environment) {
  return ThreeAddressInstruction{
      ThreeAddressOperations::SET_NOT_EQUAL, std::move(store),
      get_integer_rvalue(invert, environment), InstructionOperand(0)};
}

Instruction create_instruction_from_unary(InstructionOperand store,
                                          UnaryOperation const &unary_operation,
                                          Environment &environment) {
  switch (unary_operation.op) {
  case UnaryOperators::NEGATIVE:
    return create_negation_instruction(std::move(store),
                                       unary_operation.operand, environment);
  case UnaryOperators::INVERSION:
    return create_inversion_instruction(std::move(store),
                                        unary_operation.operand, environment);
  case UnaryOperators::DEREFERENCE:
    throw std::runtime_error("dereference operator not implemented");
  case UnaryOperators::REFERENCE:
    throw std::runtime_error("reference operator not implemented");
  case UnaryOperators::POSITIVE:
    throw std::runtime_error(
        "compiler error: positive operator found during TAC generation");
  }
}

ThreeAddressOperations binary_to_three_address_operation(BinaryOperators op) {
  switch (op) {
  case BinaryOperators::ADDITION:
    return ThreeAddressOperations::ADD;
  case BinaryOperators::SUBTRACTION:
    return ThreeAddressOperations::SUBTRACT;
  case BinaryOperators::MULTIPLICATION:
    return ThreeAddressOperations::MULTIPLY;
  case BinaryOperators::DIVISION:
    return ThreeAddressOperations::DIVIDE;
  case BinaryOperators::MODULO:
    return ThreeAddressOperations::MODULO;
  case BinaryOperators::EQUALS:
    return ThreeAddressOperations::SET_EQUAL;
  case BinaryOperators::NOT_EQUAL:
    return ThreeAddressOperations::SET_NOT_EQUAL;
  case BinaryOperators::LESS_THAN:
    return ThreeAddressOperations::SET_LESS_THAN;
  case BinaryOperators::LESS_THAN_OR_EQUAL_TO:
    return ThreeAddressOperations::SET_LESS_THAN_OR_EQUAL;
  case BinaryOperators::GREATER_THAN:
    return ThreeAddressOperations::SET_GREATER_THAN;
  case BinaryOperators::GREATER_THAN_OR_EQUAL_TO:
    return ThreeAddressOperations::SET_GREATER_THAN_OR_EQUAL;
  }
}

struct BinaryOperationToInstruction {
  BinaryOperationToInstruction(BinaryOperators op, InstructionOperand operand)
      : m_operator(op), m_store(std::move(operand)) {}

  Instruction operator()(int lhs, int rhs) {
    return TwoAddressInstruction{TwoAddressOperations::STORE,
                                 std::move(m_store),
                                 evaluate_binary(m_operator, lhs, rhs)};
  }

  template <typename T, typename U> Instruction operator()(T lhs, U rhs) {
    return ThreeAddressInstruction{
        binary_to_three_address_operation(m_operator), std::move(m_store),
        std::move(lhs), std::move(rhs)};
  }

private:
  BinaryOperators m_operator;
  InstructionOperand m_store;
};

Instruction
create_instruction_from_binary(InstructionOperand store,
                               BinaryOperation const &binary_operation,
                               Environment &environment) {
  return std::visit(
      BinaryOperationToInstruction(binary_operation.op, std::move(store)),
      get_integer_rvalue(binary_operation.lhs, environment),
      get_integer_rvalue(binary_operation.rhs, environment));
}

Instruction create_store_instruction(InstructionOperand store,
                                     Operand const &operand, Types type,
                                     Environment &environment) {
  return TwoAddressInstruction{TwoAddressOperations::STORE, std::move(store),
                               get_rvalue(operand, type, environment)};
}

InstructionOperand
create_temporary_operand(TemporaryAssignment const *temporary, Types type,
                         Environment &environment) {
  return Temporary{environment.add_temporary(temporary, type)};
}

InstructionOperand get_variable_lvalue(std::string *identifier, Types type,
                                       Environment &environment) {
  switch (type) {
  case Types::INT:
    return get_integer_lvalue(identifier, environment);
  case Types::FUNCTION:
    return get_function_lvalue(identifier, environment);
  default:
    throw std::runtime_error("attempted to use void variable '" + *identifier +
                             "' as an lvalue");
  }
}

std::optional<int> get_constant_from_operand(Operand const &operand) {
  try {
    return std::get<int>(operand);
  } catch (std::bad_variant_access &) {
    return std::nullopt;
  }
}

Instruction get_variable_store_instruction(std::string *identifier,
                                           Operand const &operand,
                                           Environment &environment) {
  auto type = environment.get_variable_type(identifier);
  if (auto constant = get_constant_from_operand(operand))
    environment.set_integer_variable(identifier, *constant);
  return create_store_instruction(
      get_variable_lvalue(identifier, type, environment), operand, type,
      environment);
}

Instruction get_parameter_push_instruction(Operand const &operand, Types type,
                                           Environment &environment) {
  return OneAddressInstruction{
      OneAddressOperations::PUSH_PARAMETER,
      std::visit(GetOperandAsRValueWithType(environment, type), operand)};
}

template <typename Procedure>
void add_parameter_push_instructions(std::vector<Operand> const &arguments,
                                     std::vector<Types> const &types,
                                     Procedure &procedure,
                                     Environment &environment) {
  for (auto i = 0u; i < arguments.size(); ++i)
    procedure.emplace_back(
        get_parameter_push_instruction(arguments[i], types[i], environment));
}

template <typename Procedure>
void add_parameter_push_instructions(std::vector<Operand> const &arguments,
                                     Procedure &procedure,
                                     Environment &environment) {
  for (auto i = 0u; i < arguments.size(); ++i)
    procedure.emplace_back(
        get_parameter_push_instruction(arguments[i], Types::ANY, environment));
}

Instruction create_pop_parameters_instruction(std::size_t number_parameters) {
  return OneAddressInstruction{OneAddressOperations::POP_PARAMETERS,
                               static_cast<int>(number_parameters)};
}

Instruction create_pop_parameters_instruction(std::vector<Types> const &types) {
  return OneAddressInstruction{OneAddressOperations::POP_PARAMETERS,
                               static_cast<int>(types.size())};
}

Instruction create_function_call(InstructionOperand operand) {
  return OneAddressInstruction{OneAddressOperations::FUNCTION_CALL,
                               std::move(operand)};
}

Instruction create_closure_call_instruction(Closure const *closure) {
  return create_function_call(ProcedureAddress{closure});
}

template <typename Procedure>
Types add_closure_call(std::string *identifier, Closure const *closure,
                       std::vector<Operand> const &arguments,
                       Procedure &procedure, Environment &environment) {
  if (arguments.size() != closure->parameter_types().size())
    throw std::runtime_error("attempted to call " + *identifier + " with " +
                             std::to_string(arguments.size()) + ", " +
                             std::to_string(closure->parameter_types().size()) +
                             " expected");
  add_parameter_push_instructions(arguments, closure->parameter_types(),
                                  procedure, environment);
  procedure.emplace_back(create_closure_call_instruction(closure));
  if (!closure->parameter_types().empty())
    procedure.emplace_back(
        create_pop_parameters_instruction(closure->parameter_types()));
  return closure->return_type();
}

template <typename Procedure>
Types add_unsafe_function_call(InstructionOperand operand,
                               std::vector<Operand> const &arguments,
                               Procedure &procedure, Environment &environment) {
  add_parameter_push_instructions(arguments, procedure, environment);
  procedure.emplace_back(create_function_call(operand));
  if (!arguments.empty())
    procedure.emplace_back(create_pop_parameters_instruction(arguments.size()));
  return Types::ANY;
}

template <typename Procedure>
Types add_function_call_from_variable(std::string *identifier,
                                      std::vector<Operand> const &arguments,
                                      Procedure &procedure,
                                      Environment &environment) {
  auto function_variable = environment.get_function_variable(identifier);
  if (auto closure = function_variable.variable.value)
    return add_closure_call(identifier, closure, arguments, procedure,
                            environment);
  else
    return add_unsafe_function_call(
        Variable{identifier, function_variable.unique_id}, arguments, procedure,
        environment);
}

template <typename Procedure>
Types add_function_call(std::string *identifier,
                        std::vector<Operand> const &arguments,
                        Procedure &procedure, Environment &environment) {
  try {
    return add_closure_call(identifier, environment.get_closure(identifier),
                            arguments, procedure, environment);
  } catch (std::out_of_range &) {
    try {
      return add_function_call_from_variable(identifier, arguments, procedure,
                                             environment);
    } catch (std::out_of_range &) {
      throw std::runtime_error("attempted to call undefined variable " +
                               *identifier);
    }
  }
}

template <typename Procedure> struct AddFunctionCall {
  AddFunctionCall(std::vector<Operand> const &arguments, Procedure &procedure,
                  Environment &environment)
      : m_arguments(arguments), m_procedure(procedure),
        m_environment(environment) {}

  Types operator()(std::string *identifier) {
    return add_function_call(identifier, m_arguments, m_procedure,
                             m_environment);
  }

  Types operator()(TemporaryAssignment const *temporary) {
    auto temporary_value = m_environment.temporary_value(temporary);
    if (temporary_value.type != Types::ANY ||
        temporary_value.type != Types::FUNCTION)
      throw std::runtime_error("integer type is not callable");
    return add_unsafe_function_call(Temporary{temporary_value.identifier},
                                    m_arguments, m_procedure, m_environment);
  }

private:
  std::vector<Operand> const &m_arguments;
  Procedure &m_procedure;
  Environment &m_environment;
};

template <typename Procedure>
Types add_function_call(FunctionCall const &function_call, Procedure &procedure,
                        Environment &environment) {
  return std::visit(
      AddFunctionCall(function_call.operands, procedure, environment),
      function_call.function_identifier);
}

Instruction
create_store_function_result_instruction(InstructionOperand operand) {
  return OneAddressInstruction{OneAddressOperations::STORE_FUNCTION_RESULT,
                               std::move(operand)};
}

template <typename Procedure> struct TemporaryAssignmentToInstructions {
  TemporaryAssignmentToInstructions(TemporaryAssignment const *temporary,
                                    Environment &environment,
                                    Procedure &procedure)
      : m_temporary(temporary), m_environment(environment),
        m_procedure(procedure) {}

  void operator()(UnaryOperation const &unary_operation) {
    m_procedure.emplace_back(create_instruction_from_unary(
        create_temporary_operand(m_temporary, Types::INT, m_environment),
        unary_operation, m_environment));
  }

  void operator()(BinaryOperation const &binary_operation) {
    m_procedure.emplace_back(create_instruction_from_binary(
        create_temporary_operand(m_temporary, Types::INT, m_environment),
        binary_operation, m_environment));
  }

  void operator()(FunctionCall const &function_call) {
    auto return_type =
        add_function_call(function_call, m_procedure, m_environment);
    m_procedure.emplace_back(create_store_function_result_instruction(
        create_temporary_operand(m_temporary, return_type, m_environment)));
  }

  void operator()(Operand const &operand) {
    auto type = std::visit(GetTypeFromOperand(m_environment), operand);
    m_procedure.emplace_back(create_store_instruction(
        create_temporary_operand(m_temporary, type, m_environment), operand,
        type, m_environment));
  }

private:
  TemporaryAssignment const *m_temporary;
  Environment &m_environment;
  Procedure &m_procedure;
};

template <typename Procedure> struct VariableAssignmentToInstructions {
  VariableAssignmentToInstructions(std::string *identifier,
                                   Environment &environment,
                                   Procedure &procedure)
      : m_identifier(identifier), m_environment(environment),
        m_procedure(procedure) {}

  void operator()(UnaryOperation const &unary_operation) {
    m_procedure.emplace_back(create_instruction_from_unary(
        get_integer_lvalue(m_identifier, m_environment), unary_operation,
        m_environment));
  }

  void operator()(BinaryOperation const &binary_operation) {
    m_procedure.emplace_back(create_instruction_from_binary(
        get_integer_lvalue(m_identifier, m_environment), binary_operation,
        m_environment));
  }

  void operator()(FunctionCall const &function_call) {
    auto return_type =
        add_function_call(function_call, m_procedure, m_environment);
    m_procedure.emplace_back(create_store_function_result_instruction(
        get_function_operand(m_identifier, m_environment)));
  }

  void operator()(Operand const &operand) {
    m_procedure.emplace_back(
        get_variable_store_instruction(m_identifier, operand, m_environment));
  }

private:
  std::string *m_identifier;
  Environment &m_environment;
  Procedure &m_procedure;
};
} // namespace

namespace Interpreter {
namespace TAC {

void temporary_assignment_to_three_address_code(
    ANormalForm::TemporaryAssignment const *temporary, Environment &environment,
    std::vector<Instruction> &procedures) {
  std::visit(
      TemporaryAssignmentToInstructions(temporary, environment, procedures),
      temporary->expression);
}

void variable_assignment_to_three_address_code(
    ANormalForm::VariableAssignment const &variable, Environment &environment,
    std::vector<Instruction> &procedures) {
  std::visit(VariableAssignmentToInstructions(variable.variable, environment,
                                              procedures),
             variable.expression);
}

InstructionOperand get_operand_as_rvalue_with_type(Operand const &operand,
                                                   Environment &environment,
                                                   Types type) {
  return std::visit(GetOperandAsRValueWithType(environment, type), operand);
}

} // namespace TAC
} // namespace Interpreter
