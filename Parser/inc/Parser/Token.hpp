#ifndef __TOKEN_H
#define __TOKEN_H

#include <string>
#include <variant>

namespace Parser {

enum class Keywords {
  AUTO,
  BREAK,
  CONTINUE,
  ELSE,
  EXTERN,
  IF,
  INT,
  FUNCTION,
  RETURN,
  VOID,
  WHILE
};

enum class Operators {
  ASSIGNMENT,
  INVERSION,
  MINUS,
  PLUS,
  MULTIPLY,
  DIVIDE,
  MODULO,
  APPLY,
  AMPERSAND
};

enum class Comparators {
  EQUALS,
  DOES_NOT_EQUAL,
  LESS_THAN_OR_EQUAL_TO,
  GREATER_THAN_OR_EQUAL_TO,
  LESS_THAN,
  GREATER_THAN
};

enum class Punctuation {
  LEFT_PARENTHESES,
  RIGHT_PARENTHESES,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  COMMA,
  SEMICOLON
};

struct Identifier {
  std::string value;
};

using Token = std::variant<Keywords, Operators, Comparators, Punctuation,
                           Identifier const *const, int, std::string>;

} // namespace Parser

#endif
