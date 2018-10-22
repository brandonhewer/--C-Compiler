#ifndef __A_NORMAL_TO_TAC_HPP_
#define __A_NORMAL_TO_TAC_HPP_

#include "Interpreter/ANormalForm/Statement.hpp"
#include "Interpreter/TAC/Instructions.hpp"

namespace Interpreter {
namespace TAC {

struct TACOutput {
  std::vector<std::vector<Instruction>> procedures;
  std::vector<std::unique_ptr<Closure>> closures;
  std::size_t main_procedure;
};

TACOutput a_normal_form_to_three_address_code(
    std::vector<ANormalForm::NormalStatement> const &a_normal);

} // namespace TAC
} // namespace Interpreter

#endif
