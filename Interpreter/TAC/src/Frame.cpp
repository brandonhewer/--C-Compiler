#include "Interpreter/TAC/Frame.hpp"
#include "Interpreter/TAC/Closure.hpp"

#include <iostream>

namespace {
using namespace Interpreter::TAC;

template <typename Map, typename T>
bool try_set_variable_in(Map variables, std::string *identifier, T value) {
  auto variable = variables.find(identifier);
  if (variables.end() != variable) {
    variable->second = std::move(value);
    return true;
  }
  return false;
}
} // namespace

namespace Interpreter {
namespace TAC {

using ANormalForm::TemporaryAssignment;

Frame::Frame()
    : m_expected_return_type(std::nullopt), m_temporaries(),
      m_integer_variables(), m_function_variables(), m_closures() {}

Frame::Frame(std::optional<Types> type)
    : m_expected_return_type(std::move(type)) {}

std::optional<Types> Frame::expected_return_type() const {
  return m_expected_return_type;
}

std::size_t Frame::number_of_integer_variables() const {
  return m_integer_variables.size();
}

std::size_t Frame::number_of_function_variables() const {
  return m_function_variables.size();
}

std::size_t Frame::number_of_temporaries() const {
  return m_temporaries.size();
}

Types Frame::get_variable_type(std::string *identifier) const {
  if (contains_integer_variable(identifier))
    return Types::INT;
  else if (contains_function_variable(identifier) ||
           contains_closure(identifier))
    return Types::FUNCTION;
  throw std::runtime_error("variable with name " + *identifier +
                           " does not exist");
}

TemporaryValue const &Frame::temporary_value(
    ANormalForm::TemporaryAssignment const *temporary) const {
  return m_temporaries.at(temporary);
}

bool Frame::contains_integer_variable(std::string *identifier) const {
  return m_integer_variables.end() != m_integer_variables.find(identifier) ||
         m_integer_parameters.find(identifier) != m_integer_parameters.end();
}

bool Frame::contains_function_variable(std::string *identifier) const {
  return m_function_variables.end() != m_function_variables.find(identifier) ||
         m_function_parameters.end() != m_function_parameters.find(identifier);
}

bool Frame::contains_closure(std::string *identifier) const {
  return m_closures.end() != m_closures.find(identifier);
}

bool Frame::contains_identifier(std::string *identifier) const {
  return contains_integer_variable(identifier) ||
         contains_function_variable(identifier) || contains_closure(identifier);
}

VariableValue<IntegerConstant>
Frame::get_integer_variable(std::string *identifier) const {
  try {
    return {m_integer_variables.at(identifier), false};
  } catch (std::out_of_range &) {
    return {m_integer_parameters.at(identifier), true};
  }
}

VariableValue<Closure *>
Frame::get_function_variable(std::string *identifier) const {
  try {
    return {m_function_variables.at(identifier), false};
  } catch (std::out_of_range &) {
    return {m_function_parameters.at(identifier), true};
  }
}

Closure const *Frame::get_closure(std::string *identifier) const {
  return m_closures.at(identifier);
}

void Frame::add_temporary(ANormalForm::TemporaryAssignment const *temporary,
                          TemporaryValue value) {
  m_temporaries[temporary] = std::move(value);
}

void Frame::declare_integer_variable(std::string *identifier) {
  if (contains_identifier(identifier))
    throw std::runtime_error("redeclaration of variable with name: " +
                             *identifier);
  m_integer_variables[identifier] = IntegerConstant();
}

void Frame::declare_function_variable(std::string *identifier) {
  if (contains_identifier(identifier))
    throw std::runtime_error("redeclaration of variable with name: " +
                             *identifier);
  m_function_variables[identifier] = nullptr;
}

void Frame::declare_integer_parameter(std::string *identifier) {
  if (contains_identifier(identifier))
    throw std::runtime_error("redeclaration of variable with name: " +
                             *identifier);
  m_integer_parameters[identifier] = IntegerConstant();
}

void Frame::declare_function_parameter(std::string *identifier) {
  if (contains_identifier(identifier))
    throw std::runtime_error("redeclaration of variable with name: " +
                             *identifier);
  m_function_parameters[identifier] = nullptr;
}

void Frame::declare_closure(std::string *identifier, Closure *closure) {
  if (contains_identifier(identifier))
    throw std::runtime_error("redeclaration of variable with name: " +
                             *identifier);
  m_closures.insert({identifier, closure});
}

bool Frame::set_integer_variable(std::string *identifier, int value) {
  try {
    m_integer_variables[identifier].value = value;
    return true;
  } catch (std::out_of_range &) {
    return false;
  }
}

bool Frame::set_function_variable(std::string *identifier, Closure *value) {
  try {
    m_function_variables[identifier] = value;
    return true;
  } catch (std::out_of_range &) {
    return false;
  }
}

bool Frame::set_closure_location(std::string *identifier,
                                 std::size_t procedure_index) {
  try {
    m_closures[identifier]->set_procedure_index(procedure_index);
    return true;
  } catch (std::out_of_range &) {
    return false;
  }
}

} // namespace TAC
} // namespace Interpreter
