#ifndef __INSTRUCTIONS_HPP_
#define __INSTRUCTIONS_HPP_

#include "Interpreter/ANormalForm/Expression.hpp"
#include "Interpreter/TAC/Closure.hpp"

#include <variant>

namespace Interpreter {
namespace TAC {

struct Temporary {
  std::size_t identifier;
};

struct Variable {
  std::string *identifier;
  std::size_t unique_id;
};

struct Parameter {
  std::string *identifier;
  std::size_t unique_id;
};

struct ProcedureAddress {
  Closure const *closure;
};

using InstructionOperand =
    std::variant<Temporary, Variable, Parameter, ProcedureAddress, int>;

enum class ThreeAddressOperations {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  MODULO,
  SET_EQUAL,
  SET_LESS_THAN,
  SET_GREATER_THAN,
  SET_GREATER_THAN_OR_EQUAL,
  SET_LESS_THAN_OR_EQUAL,
  SET_NOT_EQUAL
};

enum class TwoAddressOperations { STORE, NEGATIVE, BRANCH_IF_ZERO };

enum class OneAddressOperations {
  BRANCH,
  RETURN,
  STORE_FUNCTION_RESULT,
  FUNCTION_CALL,
  BEGIN_FUNCTION,
  PUSH_PARAMETER,
  POP_PARAMETERS
};

enum class ZeroAddressOperations {
  SYSCALL,
  END_FUNCTION,
  BREAK,
  CONTINUE,
  RETURN
};

struct ThreeAddressInstruction {
  ThreeAddressOperations op;
  InstructionOperand first_operand;
  InstructionOperand second_operand;
  InstructionOperand third_operand;
};

struct TwoAddressInstruction {
  TwoAddressOperations op;
  InstructionOperand lhs;
  InstructionOperand rhs;
};

struct OneAddressInstruction {
  OneAddressOperations op;
  InstructionOperand operand;
};

using Instruction =
    std::variant<ZeroAddressOperations, OneAddressInstruction,
                 TwoAddressInstruction, ThreeAddressInstruction>;

} // namespace TAC
} // namespace Interpreter

#endif
