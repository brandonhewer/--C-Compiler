#ifndef __FRAME_HPP_
#define __FRAME_HPP_

#include "Interpreter/ANormalForm/Expression.hpp"

#include <optional>
#include <unordered_map>

namespace Interpreter {
namespace TAC {

class Closure;

struct IntegerConstant {
  IntegerConstant(int val) : value(val) {}
  IntegerConstant() : value(std::nullopt) {}
  std::optional<int> value;
};

enum class Types { VOID, INT, FUNCTION, ANY };

struct TemporaryValue {
  Types type;
  std::size_t identifier;
};

template <typename T> struct VariableValue {
  T const &value;
  bool is_parameter;
};

class Frame {
public:
  Frame();
  Frame(std::optional<Types> type);

  std::optional<Types> expected_return_type() const;

  std::size_t number_of_integer_variables() const;
  std::size_t number_of_function_variables() const;
  std::size_t number_of_temporaries() const;
  std::size_t
  temporary_identifier(ANormalForm::TemporaryAssignment const *) const;

  TemporaryValue const &
  temporary_value(ANormalForm::TemporaryAssignment const *) const;

  bool contains_integer_variable(std::string *) const;
  bool contains_function_variable(std::string *) const;
  bool contains_closure(std::string *) const;
  bool contains_identifier(std::string *) const;

  Types get_variable_type(std::string *) const;
  VariableValue<IntegerConstant> get_integer_variable(std::string *) const;
  VariableValue<Closure *> get_function_variable(std::string *) const;
  Closure const *get_closure(std::string *) const;

  void add_temporary(ANormalForm::TemporaryAssignment const *, TemporaryValue);

  void declare_integer_variable(std::string *);
  void declare_function_variable(std::string *);
  void declare_integer_parameter(std::string *);
  void declare_function_parameter(std::string *);
  void declare_closure(std::string *, Closure *);

  bool set_integer_variable(std::string *, int value);
  bool set_function_variable(std::string *, Closure *value);
  bool set_closure_location(std::string *, std::size_t);

private:
  std::optional<Types> m_expected_return_type;
  std::unordered_map<std::string *, IntegerConstant> m_integer_parameters;
  std::unordered_map<std::string *, Closure *> m_function_parameters;
  std::unordered_map<std::string *, IntegerConstant> m_integer_variables;
  std::unordered_map<std::string *, Closure *> m_function_variables;
  std::unordered_map<std::string *, Closure *> m_closures;
  std::unordered_map<ANormalForm::TemporaryAssignment const *, TemporaryValue>
      m_temporaries;
};

} // namespace TAC
} // namespace Interpreter

#endif
