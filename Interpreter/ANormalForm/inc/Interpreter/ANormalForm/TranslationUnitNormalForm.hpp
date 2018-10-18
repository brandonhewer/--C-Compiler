#ifndef __TRANSLATION_UNIT_NORMAL_FORM_HPP_
#define __TRANSLATION_UNIT_NORMAL_FORM_HPP_

#include "Interpreter/ANormalForm/StatementNormalForm.hpp"

namespace {

struct ExternalDeclarationToNormal : public boost::static_visitor<> {

  template <typename Vector>
  void operator()(Vector &output,
                  FunctionDefinition const &function_definition) const {
    add_a_normal_function_definition(function_definition, output);
  }

  template <typename Vector>
  void operator()(Vector &output, Declaration const &declaration) const {
    add_a_normal_declaration(declaration, output);
  }
};

template <typename Vector>
void add_a_normal_external_declaration(
    ExternalDeclaration const &external_declaration, Vector &output) {
  boost::apply_visitor(
      boost::bind(ExternalDeclarationToNormal(), boost::ref(output), _1),
      external_declaration);
}

template <typename Vector>
void add_a_normal_translation_unit(TranslationUnit const &translation_unit,
                                   Vector &output) {
  for (auto &&external_declaration : translation_unit)
    add_a_normal_external_declaration(external_declaration, output);
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

std::vector<NormalStatement> normalise_translation_unit(
    Parser::AST::TranslationUnit const &translation_unit) {
  std::vector<NormalStatement> normalised;
  add_a_normal_translation_unit(translation_unit, normalised);
  return normalised;
}

} // namespace ANormalForm
} // namespace Interpreter

#endif
