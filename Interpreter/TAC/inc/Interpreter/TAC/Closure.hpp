#ifndef __CLOSURE_HPP_
#define __CLOSURE_HPP_

#include "Interpreter/TAC/Environment.hpp"

#include <memory>
#include <optional>

namespace Interpreter {
namespace TAC {

class Environment;

class Closure {
public:
  Closure(Types return_type, std::vector<Types> parameter_types);

  std::optional<std::size_t> procedure_index() const;
  Types const &return_type() const;
  std::vector<Types> const &parameter_types() const;
  Environment const &captured_environment() const;
  void capture_frame(Frame frame) const;
  void set_procedure_index(std::size_t procedure_index);

private:
  Types const m_return_type;
  std::vector<Types> const m_parameter_types;
  std::unique_ptr<Environment> m_environment;
  std::optional<std::size_t> m_procedure_index;
};

} // namespace TAC
} // namespace Interpreter

#endif
