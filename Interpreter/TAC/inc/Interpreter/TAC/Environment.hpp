#ifndef __ENVIRONMENT_HPP_
#define __ENVIRONMENT_HPP_

#include "Interpreter/TAC/Frame.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Interpreter {
namespace TAC {

template <typename T> struct VariableWithId {
  VariableValue<T> variable;
  std::size_t unique_id;
};

class Environment {
public:
  Environment();

  std::optional<Types> expected_return_type() const;

  std::size_t get_scope_level() const;
  std::size_t number_of_local_integer_variables() const;
  std::size_t number_of_local_function_variables() const;
  std::size_t number_of_local_temporaries() const;
  std::size_t number_of_temporaries() const;

  TemporaryValue const &
  temporary_value(ANormalForm::TemporaryAssignment const *) const;

  bool contains_identifier(std::string *) const;

  Types get_variable_type(std::string *) const;
  VariableWithId<IntegerConstant> get_integer_variable(std::string *) const;
  VariableWithId<Closure *> get_function_variable(std::string *) const;
  Closure const *get_closure(std::string *) const;

  std::size_t add_temporary(ANormalForm::TemporaryAssignment const *,
                            Types type);

  void declare_integer_variable(std::string *);
  void declare_function_variable(std::string *);
  void declare_integer_parameter(std::string *);
  void declare_function_parameter(std::string *);
  void declare_closure(std::string *, Types return_type,
                       std::vector<Types> parameter_types);

  void set_integer_variable(std::string *, int constant);
  void set_function_variable(std::string *, Closure *closure);

  void set_closure_location(std::string *, std::size_t);
  void move_closure_into(std::string *, std::unique_ptr<Closure>);

  void push_frame(Frame frame);
  void push_function_frame(Types type);
  void push_empty_frame();
  void pop_frame();

  void return_closure_and_pop_frame(std::string *, std::string *);
  void return_integer_and_pop_frame(std::string *, std::string *);

  std::vector<std::unique_ptr<Closure>> extract_closures();

private:
  std::size_t m_total_number_of_temporaries;
  std::vector<std::unique_ptr<Closure>> m_closures;
  std::vector<Frame> m_frames;
};

} // namespace TAC
} // namespace Interpreter

#endif