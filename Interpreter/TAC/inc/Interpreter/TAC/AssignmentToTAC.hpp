#ifndef __ASSIGNMENT_TO_TAC_HPP_
#define __ASSIGNMENT_TO_TAC_HPP_

#include "Interpreter/ANormalForm/Expression.hpp"
#include "Interpreter/TAC/Environment.hpp"
#include "Interpreter/TAC/Instructions.hpp"

namespace Interpreter {
namespace TAC {

void temporary_assignment_to_three_address_code(
    ANormalForm::TemporaryAssignment const *, Environment &,
    std::vector<Instruction> &);

void variable_assignment_to_three_address_code(
    ANormalForm::VariableAssignment const &, Environment &,
    std::vector<Instruction> &);

InstructionOperand
get_operand_as_rvalue_with_type(ANormalForm::Operand const &operand,
                                Environment &environment, Types type);

} // namespace TAC
} // namespace Interpreter

#endif
