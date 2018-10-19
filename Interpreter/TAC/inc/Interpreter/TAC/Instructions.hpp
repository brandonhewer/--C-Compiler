#ifndef __INSTRUCTIONS_HPP_
#define __INSTRUCTIONS_HPP_

#include <variant>

namespace Interpreter {
namespace TAC {

struct Register {
  std::size_t identifier;
};

using InstructionOperand = std::variant<int, Register>;

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

enum class TwoAddressOperations { STORE, LOAD, NEGATIVE, BRANCH_IF_ZERO };

enum class OneAddressOperations { BRANCH, BRANCH_AND_LINK };

enum class ZeroAddressOperations { SYSCALL };

struct ThreeAddressInstruction {
  ThreeAddressOperations op;
};

struct TwoAddressInstruction {
  TwoAddressOperations op;
};

struct OneAddressInstruction {
  OneAddressOperations op;
};

struct ZeroAddressInstruction {
  ZeroAddressOperations op;
};

} // namespace TAC
} // namespace Interpreter

#endif
