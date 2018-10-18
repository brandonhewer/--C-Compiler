#ifndef __DECLARATION_NORMAL_FORM_HPP_
#define __DECLARATION_NORMAL_FORM_HPP_

#include "Interpreter/ANormalForm/Declaration.hpp"
#include "Interpreter/ANormalForm/ExpressionNormalForm.hpp"

#include <utility>

namespace Interpreter {
namespace ANormalForm {

template <typename Vector>
void add_a_normal_declaration(Declaration const &declaration, Vector &output);

std::pair<TypeSpecifier, StorageClassSpecifier> simplify_declaration_specifiers(
    std::vector<DeclarationSpecifier> const &declaration_specifiers);

} // namespace ANormalForm
} // namespace Interpreter

namespace {

using namespace Parser::AST;
using namespace Interpreter::ANormalForm;

template <typename Vector> struct AddAssignmentTo {
  AddAssignmentTo(Vector &output, std::string *identifier)
      : m_output(output), m_identifier(identifier) {}

  void operator()(VariableAssignment const &assignment) const {
    m_output.emplace_back(
        VariableAssignment{m_identifier, Operand(assignment.variable)});
  }

  void operator()(TemporaryAssignment const &assignment) const {
    m_output.emplace_back(
        VariableAssignment{m_identifier, simplify_temporary(assignment)});
  }

  template <typename T> void operator()(T const &) const {
    throw std::runtime_error("invalid r-value given in assignment");
  }

private:
  Vector &m_output;
  std::string *m_identifier;
};

template <typename Vector>
void add_an_assignment_to_previous(std::string *identifier, Vector &output) {
  std::visit(AddAssignmentTo(output, identifier), output.back());
}

struct ExtractTypeAndStorageClass : public boost::static_visitor<> {

  void operator()(std::optional<TypeSpecifier> &type_output,
                  StorageClassSpecifier &, TypeSpecifier const &type) const {
    type_output = type;
  }

  void operator()(std::optional<TypeSpecifier> &,
                  StorageClassSpecifier &storage_class_output,
                  StorageClassSpecifier const &storage_class) const {
    storage_class_output = storage_class;
  }
};

std::pair<std::optional<TypeSpecifier>, StorageClassSpecifier>
extract_type_and_storage_class(
    std::vector<DeclarationSpecifier> const &declaration_specifiers) {
  std::optional<TypeSpecifier> type;
  StorageClassSpecifier storage_class = StorageClassSpecifier::AUTO;

  auto extractor = boost::bind(ExtractTypeAndStorageClass(), boost::ref(type),
                               boost::ref(storage_class), _1);
  for (auto &&specifier : declaration_specifiers)
    boost::apply_visitor(extractor, specifier);
  return {type, storage_class};
}

VariableDeclaration
parameter_to_variable_declaration(ParameterDeclaration const &declaration) {
  auto const specifiers =
      simplify_declaration_specifiers(declaration.specifiers);
  return VariableDeclaration{declaration.identifier, specifiers.second,
                             specifiers.first};
}

std::vector<VariableDeclaration>
parameters_to_declarations(Parameters const &parameters) {
  std::vector<VariableDeclaration> declarations;
  declarations.reserve(parameters.size());
  for (auto &&declaration : parameters)
    declarations.emplace_back(parameter_to_variable_declaration(declaration));
  return declarations;
}

VariableDeclaration
identifier_to_variable_declaration(std::string *identifier) {
  return VariableDeclaration{identifier, StorageClassSpecifier::AUTO,
                             TypeSpecifier::INT};
}

std::vector<VariableDeclaration>
identifiers_to_variable_declaration(Identifiers const &identifiers) {
  std::vector<VariableDeclaration> declarations;
  declarations.reserve(identifiers.size());
  for (auto &&identifier : identifiers)
    declarations.emplace_back(identifier_to_variable_declaration(identifier));
  return declarations;
}

struct ParametersOrIdentifiersToDeclarations
    : public boost::static_visitor<std::vector<VariableDeclaration>> {

  std::vector<VariableDeclaration>
  operator()(Parameters const &parameters) const {
    return parameters_to_declarations(parameters);
  }

  std::vector<VariableDeclaration>
  operator()(Identifiers const &identifiers) const {
    return identifiers_to_variable_declaration(identifiers);
  }
} parameters_or_identifiers_to_declarations_;

std::vector<VariableDeclaration> parameters_or_identifiers_to_declarations(
    ParametersOrIdentifiers const &parameters_or_identifiers) {
  return boost::apply_visitor(parameters_or_identifiers_to_declarations_,
                              parameters_or_identifiers);
}

struct GetIdentifierFromDeclarator
    : public boost::static_visitor<std::string *> {

  std::string *operator()(std::string *identifier) const { return identifier; }

  std::string *operator()(FunctionDeclarator const &declarator) const {
    return declarator.identifier;
  }
} get_identifier_from_declarator_;

struct DeclarationToNormal : public boost::static_visitor<> {
  DeclarationToNormal(TypeSpecifier type, StorageClassSpecifier storage_class)
      : m_type(type), m_storage_class(storage_class) {}

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output, std::string *identifier) const {
    output.emplace_back(
        VariableDeclaration{identifier, m_storage_class, m_type});
  }

  template <typename... Ts>
  void operator()(std::vector<Ts...> &output,
                  FunctionDeclarator const &declarator) const {
    add_a_normal_function_declaration(m_type, m_storage_class, declarator,
                                      output);
  }

private:
  TypeSpecifier const m_type;
  StorageClassSpecifier const m_storage_class;
};

std::string *get_identifier_from_declarator(Declarator const &declarator) {
  return boost::apply_visitor(get_identifier_from_declarator_, declarator);
}

template <typename... Ts>
void add_a_normal_init_declaration(TypeSpecifier const &type,
                                   StorageClassSpecifier const &storage_class,
                                   InitDeclarator const &init_declarator,
                                   std::vector<Ts...> &output) {
  auto declaration_to_normal = boost::bind(
      DeclarationToNormal(type, storage_class), boost::ref(output), _1);
  boost::apply_visitor(declaration_to_normal, init_declarator.declarator);

  if (auto declared_value = init_declarator.assignment) {
    add_a_normal_assignment_expression(*declared_value, output);
    add_an_assignment_to_previous(
        get_identifier_from_declarator(init_declarator.declarator), output);
  }
}

template <typename... Ts>
void add_a_normal_declaration(Declaration const &declaration,
                              std::vector<Ts...> &output) {
  auto const specifiers =
      simplify_declaration_specifiers(declaration.specifiers);

  for (auto &&declarator : declaration.declarators)
    add_a_normal_init_declaration(specifiers.first, specifiers.second,
                                  declarator, output);
}

} // namespace

namespace Interpreter {
namespace ANormalForm {

std::pair<TypeSpecifier, StorageClassSpecifier> simplify_declaration_specifiers(
    std::vector<DeclarationSpecifier> const &declaration_specifiers) {
  if (declaration_specifiers.size() > 2)
    throw std::runtime_error("invalid declaration; only a single type and "
                             "storage class may be defined");

  auto const extracted = extract_type_and_storage_class(declaration_specifiers);
  if (auto type = extracted.first)
    return {*type, extracted.second};
  return {TypeSpecifier::INT, extracted.second};
}

template <typename Vector>
void add_a_normal_declaration(Declaration const &declaration, Vector &output) {
  auto const specifiers =
      simplify_declaration_specifiers(declaration.specifiers);

  for (auto &&declarator : declaration.declarators)
    add_a_normal_init_declaration(specifiers.first, specifiers.second,
                                  declarator, output);
}

template <typename Vector>
void add_a_normal_function_declaration(
    TypeSpecifier const &type, StorageClassSpecifier const &storage_class,
    FunctionDeclarator const &declarator, Vector &output) {
  output.emplace_back(FunctionDeclaration{
      declarator.identifier, storage_class, type,
      parameters_or_identifiers_to_declarations(declarator.parameters)});
}

} // namespace ANormalForm
} // namespace Interpreter

#endif
