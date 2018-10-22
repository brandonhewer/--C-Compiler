#include "Interpreter/TAC/Closure.hpp"
#include "Interpreter/TAC/Environment.hpp"

namespace Interpreter {
namespace TAC {

Closure::Closure(Types return_type, std::vector<Types> parameter_types)
    : m_return_type(return_type), m_parameter_types(std::move(parameter_types)),
      m_environment(), m_procedure_index(std::nullopt) {}

std::optional<std::size_t> Closure::procedure_index() const {
  return m_procedure_index;
}

Types const &Closure::return_type() const { return m_return_type; }

std::vector<Types> const &Closure::parameter_types() const {
  return m_parameter_types;
}

Environment const &Closure::captured_environment() const {
  return *m_environment;
}

void Closure::capture_frame(Frame frame) const {
  m_environment->push_frame(std::move(frame));
}

void Closure::set_procedure_index(std::size_t procedure_index) {
  m_procedure_index = procedure_index;
}

} // namespace TAC
} // namespace Interpreter