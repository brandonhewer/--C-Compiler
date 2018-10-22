#include "Interpreter/TAC/PrintTAC.hpp"
#include "Interpreter/TAC/Instructions.hpp"

#include <boost/algorithm/string/join.hpp>

namespace {

using namespace Interpreter::TAC;

struct InstructionOperandToString {

  std::string operator()(Temporary const &temp) const {
    return "_t" + std::to_string(temp.identifier);
  }

  std::string operator()(Variable const &variable) const {
    return *variable.identifier + std::to_string(variable.unique_id);
  }

  std::string operator()(ProcedureAddress const &procedure) const {
    return "L" + std::to_string(*procedure.closure->procedure_index());
  }

  std::string operator()(Parameter const &parameter) const {
    return "_p" + *parameter.identifier + std::to_string(parameter.unique_id);
  }

  std::string operator()(int procedure) const {
    return std::to_string(procedure);
  }
};

std::string operand_to_string(InstructionOperand const &operand) {
  return std::visit(InstructionOperandToString(), operand);
}

std::string zero_address_to_string(ZeroAddressOperations const &operation) {
  switch (operation) {
  case ZeroAddressOperations::SYSCALL:
    return "SYSCALL";
  case ZeroAddressOperations::END_FUNCTION:
    return "EndFunction";
  case ZeroAddressOperations::BREAK:
    return "Break";
  case ZeroAddressOperations::CONTINUE:
    return "Continue";
  case ZeroAddressOperations::RETURN:
    return "Return";
  }
}

std::string one_address_to_string(OneAddressInstruction const &instruction) {
  switch (instruction.op) {
  case OneAddressOperations::BRANCH:
    return "Branch " + operand_to_string(instruction.operand);
  case OneAddressOperations::RETURN:
    return "Return " + operand_to_string(instruction.operand);
  case OneAddressOperations::STORE_FUNCTION_RESULT:
    return "StoreFunctionReturn " + operand_to_string(instruction.operand);
  case OneAddressOperations::FUNCTION_CALL:
    return "LCall " + operand_to_string(instruction.operand);
  case OneAddressOperations::BEGIN_FUNCTION:
    return "BeginFunction " + operand_to_string(instruction.operand);
  case OneAddressOperations::PUSH_PARAMETER:
    return "PushParameter " + operand_to_string(instruction.operand);
  case OneAddressOperations::POP_PARAMETERS:
    return "PopParameters " + operand_to_string(instruction.operand);
  }
}

std::string two_address_to_string(TwoAddressInstruction const &instruction) {
  switch (instruction.op) {
  case TwoAddressOperations::STORE:
    return operand_to_string(instruction.lhs) + " = " +
           operand_to_string(instruction.rhs);
  case TwoAddressOperations::NEGATIVE:
    return operand_to_string(instruction.lhs) + " = -" +
           operand_to_string(instruction.rhs);
  case TwoAddressOperations::BRANCH_IF_ZERO:
    return "BranchIfZero " + operand_to_string(instruction.lhs) +
           operand_to_string(instruction.rhs);
  }
}

std::string
three_address_to_string(ThreeAddressInstruction const &instruction) {
  switch (instruction.op) {
  case ThreeAddressOperations::ADD:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " + " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SUBTRACT:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " - " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::MULTIPLY:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " * " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::DIVIDE:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " / " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::MODULO:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " % " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SET_EQUAL:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) +
           " == " + operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SET_LESS_THAN:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " < " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SET_GREATER_THAN:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) + " > " +
           operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SET_GREATER_THAN_OR_EQUAL:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) +
           " >= " + operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SET_LESS_THAN_OR_EQUAL:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) +
           " <= " + operand_to_string(instruction.third_operand);
  case ThreeAddressOperations::SET_NOT_EQUAL:
    return operand_to_string(instruction.first_operand) + " = " +
           operand_to_string(instruction.second_operand) +
           " != " + operand_to_string(instruction.third_operand);
  }
}

struct InstructionToString {

  std::string operator()(ZeroAddressOperations const &operation) const {
    return zero_address_to_string(operation);
  }

  std::string operator()(OneAddressInstruction const &instruction) const {
    return one_address_to_string(instruction);
  }

  std::string operator()(TwoAddressInstruction const &instruction) const {
    return two_address_to_string(instruction);
  }

  std::string operator()(ThreeAddressInstruction const &instruction) const {
    return three_address_to_string(instruction);
  }
};

auto instruction_string_creator(std::size_t indent) {
  return [&](Instruction const &instruction) {
    return "  " + std::visit(InstructionToString(), instruction);
  };
}

std::string
get_instructions_to_string(std::vector<Instruction> const &instructions) {
  std::vector<std::string> instruction_strings;
  instruction_strings.reserve(instructions.size());
  std::transform(instructions.begin(), instructions.end(),
                 std::back_inserter(instruction_strings),
                 instruction_string_creator(2));
  return boost::algorithm::join(instruction_strings, "\n");
}

} // namespace

namespace Interpreter {
namespace TAC {

std::ostream &operator<<(std::ostream &output_stream, TACOutput const &tac) {
  for (auto i = 0u; i < tac.procedures.size(); ++i) {
    if (i == tac.main_procedure)
      output_stream << "main"
                    << ":\n";
    else
      output_stream << "L" << i << ":\n";
    output_stream << get_instructions_to_string(tac.procedures[i]) << "\n";
  }
  return output_stream;
}

std::ostream &operator<<(std::ostream &output_stream,
                         std::vector<Instruction> const &procedure) {
  return output_stream << get_instructions_to_string(procedure);
}

} // namespace TAC
} // namespace Interpreter
