#include "Interpreter/TAC/Environment.hpp"

namespace {

Value &get_mutable_variable(std::vector<Frame> &frames,
                            std::string *identifier) {
  for (auto &&frame : frames) {
    auto variable_iterator =
  }
}

template <typename F>
auto extract_from_environment(std::vector<Frame> &frames,
                              std::string *identifier, F &&extractor) {
  for (auto frame_it = frames.rbegin(); frame_it < frames.rend(); ++frame_it) {
    auto it = frame->find(identifier);
    if (frame->end() != it)
      return extractor(it->second);
  }
  throw std::runtime_error("no such variable exists: " + *identifier);
}

} // namespace

namespace Interpreter {
namespace TAC {

Environment::Environment() : m_frames() {}

bool Environment::has_identifier_value(std::string *identifier) const {
  try {
    return extract_from_environment(m_frames, identifier,
                                    [](Value const &) { return true; });
  } catch (std::runtime_error &) {
    return false;
  }
}

Value const &Environment::get_identifier_value(std::string *identifier) const {
  return extract_from_environment(m_frames, identifier,
                                  [](Value const &value) { return value });
}

void Environment::declare_variable(std::string *identifier, Value value) {
  auto const &frame = m_frames.back();
  if (frame.end() != frame.find(identifier))
    throw std::runtime_error("redeclaration of variable " + *identifier);
  frame[identifier] = std::move(value);
}

void Environment::set_variable(std::string *identifier, Value value) {
  Value &current_value = extract_from_environment(
      m_frames, identifier, [](Value &value) { return value; });
  current_value = std::move(value);
}

void Environment::pop_frame() { m_frames.pop_back(); }

} // namespace TAC
} // namespace Interpreter
