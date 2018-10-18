#include "Interpreter/ANormalForm/Environment.hpp"

namespace Interpreter {
namespace ANormalForm {

Environment::Environment() : m_frames() {}

bool Environment::has_identifier_value(std::string *identifier) const {
  for (auto &&frame : m_frames) {
    if (frame.end() != frame.find(identifier))
      return true;
  }
  return false;
}

Value const &Environment::get_identifier_value(std::string *identifier) const {
  for (auto &&frame : m_frames) {
    auto it = frame.find(identifier);
    if (frame.end() != it)
      return it->second;
  }
  throw std::runtime_error("");
}

void Environment::pop_frame() { m_frames.pop_back(); }

} // namespace AST
} // namespace Interpreter
