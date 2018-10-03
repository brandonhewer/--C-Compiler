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

enum class MetaOperators {
  DECLARE,
  DECLARE_FUNCTION,
  DEFINE_FUNCTION,
  DEFINE_FUNCTION_HEADER,
  DEFINE_FUNCTION_CALL_INTERFACE,
  DECLARE_ABSTRACT,
  COMPOSE_TYPE_SPECIFIERS,
  COMPOUND_STATEMENTS,
  SEPARATE,
  ADD_TO_TRANSLATION_UNIT
};

enum class Comparators {
  EQUALS,
  DOES_NOT_EQUAL,
  LESS_THAN_OR_EQUAL_TO,
  GREATER_THAN_OR_EQUAL_TO,
  LESS_THAN,
  GREATER_THAN
};

struct Identifier {
  std::string value;
};

struct Pointer {
  int depth;
};

using Token =
    std::variant<Keywords, Operators, MetaOperators, Comparators,
                 Pointer, Identifier const *const, int, std::string>;

} // namespace Parser

#endif
