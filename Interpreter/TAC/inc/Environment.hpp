#ifndef __ENVIRONMENT_HPP_
#define __ENVIRONMENT_HPP_

#include "Interpreter/ANormalForm/Closure.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Interpreter {
namespace ANormalForm {

using Value = std::variant<int, Closure>;
using Frame = std::unordered_map<std::string *, Value>;

class Environment {
  Environment();

  bool has_identifier_value(std::string *identifier) const;
  Value const &get_identifier_value(std::string *identifier) const;

  template <typename... Ts> void push_frame(Ts... frame);
  void pop_frame();

private:
  std::vector<Frame> m_frames;
};

template <typename... Ts> void Environment::push_frame(Ts... frame) {
  m_frames.emplace_back(std::forward<Ts>(frame)...);
}

} // namespace ANormalForm
} // namespace Interpreter

#endif