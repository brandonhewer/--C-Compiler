#include "Interpreter/TAC/Environment.hpp"
#include "Interpreter/TAC/Closure.hpp"

namespace {

using namespace Interpreter::TAC;

auto environment_contains(std::vector<Frame> const &frames,
                          std::string *identifier) {
  for (auto frame = frames.rbegin(); frame < frames.rend(); ++frame) {
    if (frame->contains_identifier(identifier))
      return true;
  }
  return false;
}

template <typename T>
VariableValue<T> get_variable_value(T value, std::size_t scope) {
  return {std::move(value), scope};
}

} // namespace

namespace Interpreter {
namespace TAC {

Environment::Environment() : m_frames(), m_total_number_of_temporaries(0) {}

std::optional<Types> Environment::expected_return_type() const {
  if (m_frames.empty())
    return std::nullopt;
  return m_frames.back().expected_return_type();
}

std::size_t Environment::get_scope_level() const { return m_frames.size(); }

std::size_t Environment::number_of_local_integer_variables() const {
  return m_frames.back().number_of_integer_variables();
}

std::size_t Environment::number_of_local_function_variables() const {
  return m_frames.back().number_of_function_variables();
}

std::size_t Environment::number_of_local_temporaries() const {
  return m_frames.back().number_of_temporaries();
}

std::size_t Environment::number_of_temporaries() const {
  return m_total_number_of_temporaries;
}

TemporaryValue const &Environment::temporary_value(
    ANormalForm::TemporaryAssignment const *temporary) const {
  return m_frames.back().temporary_value(temporary);
}

bool Environment::contains_identifier(std::string *identifier) const {
  return environment_contains(m_frames, identifier);
}

Types Environment::get_variable_type(std::string *identifier) const {
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    try {
      return frame->get_variable_type(identifier);
    } catch (std::runtime_error &) {
    }
  }
  throw std::runtime_error("variable with name " + *identifier +
                           " does not exist");
}

VariableWithId<IntegerConstant>
Environment::get_integer_variable(std::string *identifier) const {
  std::size_t scope = get_scope_level();
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    try {
      return {frame->get_integer_variable(identifier), scope};
    } catch (std::out_of_range &) {
      scope -= 1;
    }
  }
  throw std::out_of_range("no such integer variable exists: " + *identifier);
}

VariableWithId<Closure *>
Environment::get_function_variable(std::string *identifier) const {
  std::size_t scope = get_scope_level();
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    try {
      return {frame->get_function_variable(identifier), scope};
    } catch (std::out_of_range &) {
      scope -= 1;
    }
  }
  throw std::out_of_range("no such function variable exists: " + *identifier);
}

void Environment::declare_integer_parameter(std::string *identifier) {
  if (m_frames.back().contains_identifier(identifier))
    throw std::runtime_error("attempted redeclaration of " + *identifier);
  m_frames.back().declare_integer_parameter(identifier);
}

void Environment::declare_function_parameter(std::string *identifier) {
  if (m_frames.back().contains_identifier(identifier))
    throw std::runtime_error("attempted redeclaration of " + *identifier);
  m_frames.back().declare_function_parameter(identifier);
}

Closure const *Environment::get_closure(std::string *identifier) const {
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    try {
      return frame->get_closure(identifier);
    } catch (std::out_of_range &) {
    }
  }
  throw std::out_of_range("no such function exists: " + *identifier);
}

std::size_t
Environment::add_temporary(ANormalForm::TemporaryAssignment const *temporary,
                           Types type) {
  m_frames.back().add_temporary(temporary,
                                {type, ++m_total_number_of_temporaries});
  return m_total_number_of_temporaries;
}

void Environment::declare_integer_variable(std::string *identifier) {
  if (m_frames.back().contains_identifier(identifier))
    throw std::runtime_error("attempted redeclaration of " + *identifier);
  m_frames.back().declare_integer_variable(identifier);
}

void Environment::declare_function_variable(std::string *identifier) {
  if (m_frames.back().contains_identifier(identifier))
    throw std::runtime_error("attempted redeclaration of " + *identifier);
  m_frames.back().declare_function_variable(identifier);
}

void Environment::declare_closure(std::string *identifier, Types return_type,
                                  std::vector<Types> parameter_types) {
  if (m_frames.back().contains_identifier(identifier))
    throw std::runtime_error("attempted redeclaration of " + *identifier);
  m_closures.emplace_back(
      std::make_unique<Closure>(return_type, std::move(parameter_types)));
  m_frames.back().declare_closure(identifier, m_closures.back().get());
}

void Environment::set_integer_variable(std::string *identifier, int constant) {
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    if (frame->set_integer_variable(identifier, constant))
      return;
  }
  throw std::runtime_error("no such integer variable exists: " + *identifier);
}

void Environment::set_function_variable(std::string *identifier,
                                        Closure *closure) {
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    if (frame->set_function_variable(identifier, closure))
      return;
  }
  throw std::runtime_error("no such function variable exists: " + *identifier);
}

void Environment::set_closure_location(std::string *identifier,
                                       std::size_t index) {
  for (auto frame = m_frames.rbegin(); frame < m_frames.rend(); ++frame) {
    if (frame->set_closure_location(identifier, index))
      return;
  }
  throw std::runtime_error("no such function exists: " + *identifier);
}

void Environment::move_closure_into(std::string *identifier,
                                    std::unique_ptr<Closure> closure) {}

void Environment::push_frame(Frame frame) {
  m_frames.emplace_back(std::move(frame));
}

void Environment::push_function_frame(Types type) {
  m_frames.emplace_back(Frame(type));
}

void Environment::push_empty_frame() {
  m_frames.emplace_back(Frame(expected_return_type()));
}

void Environment::pop_frame() { m_frames.pop_back(); }

void Environment::return_closure_and_pop_frame(std::string *, std::string *) {}

void Environment::return_integer_and_pop_frame(std::string *, std::string *) {}

std::vector<std::unique_ptr<Closure>> Environment::extract_closures() {
  return std::move(m_closures);
}

} // namespace TAC
} // namespace Interpreter
