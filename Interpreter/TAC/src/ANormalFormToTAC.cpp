#include "Interpreter/TAC/ANormalFormToTAC.hpp"
#include "Interpreter/TAC/AssignmentToTAC.hpp"
#include "Interpreter/TAC/Environment.hpp"

namespace {

using namespace Interpreter::ANormalForm;
using namespace Interpreter::TAC;
using namespace Parser::AST;

void generate_three_address_code(std::vector<NormalStatement> const &a_normal,
                                 Environment &environment,
                                 TACOutput &procedures);

Types type_specifier_to_value_type(TypeSpecifier specifier) {
  switch (specifier) {
  case TypeSpecifier::FUNCTION:
    return Types::FUNCTION;
  case TypeSpecifier::INT:
    return Types::INT;
  case TypeSpecifier::VOID:
    return Types::VOID;
  }
}

void declare_variable_in_environment(VariableDeclaration const &declaration,
                                     Environment &environment) {
  switch (declaration.type) {
  case TypeSpecifier::INT:
    environment.declare_integer_variable(declaration.name);
    break;
  case TypeSpecifier::FUNCTION:
    environment.declare_function_variable(declaration.name);
    break;
  case TypeSpecifier::VOID:
    throw std::runtime_error("'void' is not a valid variable type: " +
                             *declaration.name);
    break;
  }
}

void declare_parameter_in_environment(VariableDeclaration const &declaration,
                                      Environment &environment) {
  switch (declaration.type) {
  case TypeSpecifier::INT:
    environment.declare_integer_parameter(declaration.name);
    break;
  case TypeSpecifier::FUNCTION:
    environment.declare_function_parameter(declaration.name);
    break;
  case TypeSpecifier::VOID:
    throw std::runtime_error("'void' is not a valid parameter type: " +
                             *declaration.name);
    break;
  }
}

void declare_function_parameters_in_environment(
    std::vector<VariableDeclaration> const &declarations,
    Environment &environment) {
  for (auto &&declaration : declarations)
    declare_parameter_in_environment(declaration, environment);
}

void declare_function_in_environment(FunctionDeclaration const &declaration,
                                     Environment &environment,
                                     std::size_t position) {
  std::vector<Types> parameter_types;
  for (auto &&parameter : declaration.declarations)
    parameter_types.emplace_back(type_specifier_to_value_type(parameter.type));
  environment.declare_closure(declaration.name,
                              type_specifier_to_value_type(declaration.type),
                              std::move(parameter_types));
  environment.set_closure_location(declaration.name, position);
}

void try_declare_function_in_environment(FunctionDeclaration const &declaration,
                                         Environment &environment,
                                         std::size_t position) {
  try {
    declare_function_in_environment(declaration, environment, position);
  } catch (std::runtime_error &) {
  }
}

Instruction create_begin_function_instruction(int parameters) {
  return OneAddressInstruction{OneAddressOperations::BEGIN_FUNCTION,
                               InstructionOperand(parameters)};
}

int get_parameters_required_for_top_frame(Environment &environment) {
  std::size_t integers = environment.number_of_local_integer_variables();
  std::size_t functions = environment.number_of_local_function_variables();
  std::size_t temporaries = environment.number_of_local_temporaries();
  return static_cast<int>(integers + functions + temporaries);
}

Types specifier_to_type(TypeSpecifier specifier) {
  switch (specifier) {
  case TypeSpecifier::INT:
    return Types::INT;
  case TypeSpecifier::FUNCTION:
    return Types::FUNCTION;
  case TypeSpecifier::VOID:
    return Types::VOID;
  }
}

void a_normal_function_definition_to_tac(
    NormalFunctionDefinition const &definition, Environment &environment,
    TACOutput &tac) {
  try_declare_function_in_environment(definition.declaration, environment,
                                      tac.procedures.size());
  environment.push_function_frame(
      specifier_to_type(definition.declaration.type));
  declare_function_parameters_in_environment(
      definition.declaration.declarations, environment);
  tac.procedures.emplace_back(std::vector<Instruction>());

  auto const initial = tac.procedures.size() - 1;
  tac.procedures[initial].emplace_back(create_begin_function_instruction(0));
  generate_three_address_code(definition.body->statements, environment, tac);
  tac.procedures[initial].front() = create_begin_function_instruction(
      get_parameters_required_for_top_frame(environment));
  tac.procedures[initial].emplace_back(ZeroAddressOperations::END_FUNCTION);
  environment.pop_frame();
}

void add_a_normal_function_definition_to_tac(
    NormalFunctionDefinition const &definition, Environment &environment,
    TACOutput &tac) {
  if (environment.get_scope_level() == 1 &&
      *definition.declaration.name == "main")
    tac.main_procedure = tac.procedures.size();
  a_normal_function_definition_to_tac(definition, environment, tac);
}

template <typename Procedure>
void add_a_normal_return_to_tac(std::optional<Operand> const &return_value,
                                Procedure &procedure,
                                Environment &environment) {
  auto return_type = environment.expected_return_type();
  if (!return_type && !return_value)
    procedure.emplace_back(ZeroAddressOperations::RETURN);
  else if (!return_type)
    throw std::runtime_error("return value not expected");
  else if (!return_value)
    throw std::runtime_error("return value expected");
  procedure.emplace_back(
      OneAddressInstruction{OneAddressOperations::RETURN,
                            get_operand_as_rvalue_with_type(
                                *return_value, environment, *return_type)});
}

std::vector<Instruction>
variable_assignment_to_tac(VariableAssignment const &variable,
                           Environment &environment) {
  std::vector<Instruction> instructions;
  variable_assignment_to_three_address_code(variable, environment,
                                            instructions);
  return instructions;
}

std::vector<Instruction>
temporary_assignment_to_tac(TemporaryAssignment const *temporary,
                            Environment &environment) {
  std::vector<Instruction> instructions;
  temporary_assignment_to_three_address_code(temporary, environment,
                                             instructions);
  return instructions;
}

struct ANormalStatementToTAC {
  ANormalStatementToTAC(TACOutput &tac, Environment &environment)
      : m_tac(tac), m_environment(environment) {
    m_procedure_index = static_cast<int>(m_tac.procedures.size()) - 1;
  }

  void operator()(VariableAssignment const &variable) {
    if (m_procedure_index < 0)
      variable_assignment_to_tac(variable, m_environment);
    else
      variable_assignment_to_three_address_code(
          variable, m_environment, m_tac.procedures[m_procedure_index]);
  }

  void operator()(std::unique_ptr<TemporaryAssignment> const &temporary) {
    if (m_procedure_index < 0)
      temporary_assignment_to_tac(temporary.get(), m_environment);
    else
      temporary_assignment_to_three_address_code(
          temporary.get(), m_environment, m_tac.procedures[m_procedure_index]);
  }

  void operator()(VariableDeclaration const &declaration) {
    declare_variable_in_environment(declaration, m_environment);
  }

  void operator()(FunctionDeclaration const &declaration) {
    declare_function_in_environment(declaration, m_environment,
                                    m_tac.procedures.size());
  }

  void operator()(JumpKeywords jump_keyword) {
    switch (jump_keyword) {
    case JumpKeywords::BREAK:
      m_tac.procedures.back().emplace_back(ZeroAddressOperations::BREAK);
      break;
    case JumpKeywords::CONTINUE:
      m_tac.procedures.back().emplace_back(ZeroAddressOperations::CONTINUE);
      break;
    }
  }

  void operator()(NormalFunctionDefinition const &function_definition) {
    add_a_normal_function_definition_to_tac(function_definition, m_environment,
                                            m_tac);
  }

  void operator()(
      std::unique_ptr<NormalCompoundStatement> const &compound_statement) {
    throw std::runtime_error("compound statements not yet implemented");
  }

  void operator()(NormalIf const &normal_if) {}

  void operator()(NormalIfElse const &if_else) {}

  void operator()(NormalWhile const &normal_while) {}

  void operator()(NormalReturn const &normal_return) {
    add_a_normal_return_to_tac(normal_return.value,
                               m_tac.procedures[m_procedure_index],
                               m_environment);
  }

private:
  int m_procedure_index;
  TACOutput &m_tac;
  Environment &m_environment;
};

void generate_three_address_code(std::vector<NormalStatement> const &a_normal,
                                 Environment &environment,
                                 TACOutput &procedures) {
  ANormalStatementToTAC statement_to_tac(procedures, environment);
  for (auto &&statement : a_normal)
    std::visit(statement_to_tac, statement);
}

} // namespace

namespace Interpreter {
namespace TAC {

TACOutput a_normal_form_to_three_address_code(
    std::vector<ANormalForm::NormalStatement> const &a_normal) {
  TACOutput tac;
  Environment environment;
  environment.push_empty_frame();
  generate_three_address_code(a_normal, environment, tac);
  tac.closures = environment.extract_closures();
  return tac;
}

} // namespace TAC
} // namespace Interpreter
