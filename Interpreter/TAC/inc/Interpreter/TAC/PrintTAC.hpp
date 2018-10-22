#ifndef __PRINT_TAC_HPP_
#define __PRINT_TAC_HPP_

#include "Interpreter/TAC/ANormalFormToTAC.hpp"

#include <ostream>

namespace Interpreter {
namespace TAC {

std::ostream &operator<<(std::ostream &output_stream, TACOutput const &tac);

std::ostream &operator<<(std::ostream &output_stream,
                         std::vector<Instruction> const &procedure);

} // namespace TAC
} // namespace Interpreter

#endif
