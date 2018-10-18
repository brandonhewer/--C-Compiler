#ifndef __RULES_HPP_
#define __RULES_HPP_

#include "Parser/AST/ASTAdapted.hpp"
#include "Parser/Annotation/Tags.hpp"

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace Parser {
namespace Grammar {

x3::rule<primary_expression_tag, AST::PrimaryExpression>
    primary_expression("primary_expression");

x3::rule<postfix_expression_tag, AST::PostfixExpression>
    postfix_expression("postfix_expression");

x3::rule<function_application_tag, AST::FunctionApplication>
    function_application("function_application");

x3::rule<argument_expression_list_tag, AST::Expression>
    argument_expression_list("argument_expression_list");

x3::rule<argument_expression_lists_tag, std::vector<AST::Expression>>
    argument_expression_lists("argument_expression_lists");

x3::rule<unary_expression_tag, AST::UnaryExpression>
    unary_expression("unary_expression");

x3::rule<multiply_tag, AST::Multiplication> multiply("multiply");

x3::rule<divide_tag, AST::Division> divide("divide");

x3::rule<modulo_tag, AST::Modulo> modulo("modulo");

x3::rule<multiplicative_expression_tag, AST::MultiplicativeExpression>
    multiplicative_expression("multiplicative_expression");

x3::rule<addition_tag, AST::Addition> addition("addition");

x3::rule<subtraction_tag, AST::Subtraction> subtraction("subtraction");

x3::rule<less_than_tag, AST::LessThan> less_than("less_than");

x3::rule<less_than_or_equal_to_tag, AST::LessThanOrEqualTo>
    less_than_or_equal_to("less_than_or_equal_to");

x3::rule<greater_than_tag, AST::GreaterThan> greater_than("greater_than");

x3::rule<greater_than_or_equal_to_tag, AST::GreaterThanOrEqualTo>
    greater_than_or_equal_to("greater_than_or_equal_to");

x3::rule<additive_expression_tag, AST::AdditiveExpression>
    additive_expression("additive_expression");

x3::rule<relational_expression_tag, AST::RelationalExpression>
    relational_expression("relational_expression");

x3::rule<equality_check_tag, AST::Equals> equality_check("equality_check");

x3::rule<not_equal_tag, AST::NotEqual> not_equal("not_equal");

x3::rule<equality_expression_tag, AST::EqualityExpression>
    equality_expression("equality_expression");

x3::rule<assignment_tag, AST::Assignment> assignment("assignment");

x3::rule<assignment_expression_tag, AST::AssignmentExpression>
    assignment_expression("assignment_expression");

x3::rule<expression_tag, AST::Expression> expression("expression");

x3::rule<declaration_specifier_tag, AST::DeclarationSpecifier>
    declaration_specifier("declaration_specifier");

x3::rule<declaration_specifiers_tag, std::vector<AST::DeclarationSpecifier>>
    declaration_specifiers("declaration_specifiers");

x3::rule<declaration_specifiers_or_none_tag,
         std::vector<AST::DeclarationSpecifier>>
    declaration_specifiers_or_none("declaration_specifiers_or_none");

x3::rule<init_declarator_list_tag, std::vector<AST::InitDeclarator>>
    init_declarator_list("init_declarator_list");

x3::rule<declaration_tag, AST::Declaration> declaration("declaration");

x3::rule<struct _, std::string *>
    identifier_in_brackets("identifier_in_brackets");

x3::rule<init_declarator_tag, AST::InitDeclarator>
    init_declarator("init_declarator");

x3::rule<parameters_or_identifiers_tag, AST::ParametersOrIdentifiers>
    parameters_or_identifiers("parameters_or_identifiers");

x3::rule<function_declarator_tag, AST::FunctionDeclarator>
    function_declarator("function_declarator");

x3::rule<declarator_tag, AST::Declarator> declarator("declarator");

x3::rule<parameter_list_tag, AST::Parameters> parameter_list("parameter_list");

x3::rule<parameter_declaration_tag, AST::ParameterDeclaration>
    parameter_declaration("parameter_declaration");

x3::rule<identifier_list_tag, std::vector<std::string *>>
    identifier_list("identifier_list");

x3::rule<statement_tag, AST::Statement> statement("statement");

x3::rule<declaration_statement_or_function_tag,
         AST::DeclarationStatementOrFunction>
    declaration_statement_or_function("declaration_statement_or_function");

x3::rule<compound_statement_tag, AST::CompoundStatement>
    compound_statement("compound_statement");

x3::rule<statement_list_tag, std::vector<AST::Statement>>
    statement_list("statement_list");

x3::rule<expression_statement_tag, AST::Expression>
    expression_statement("expression_statement");

x3::rule<if_statement_tag, AST::If> if_statement("if_statement");

x3::rule<if_else_statement_tag, AST::IfElse>
    if_else_statement("if_else_statement");

x3::rule<iteration_statement_tag, AST::While>
    iteration_statement("iteration_statement");

x3::rule<return_statement_tag, AST::Return> return_statement("jump_statement");

x3::rule<jump_statement_tag, AST::JumpStatement>
    jump_statement("jump_statement");

x3::rule<function_definition_tag, AST::FunctionDefinition>
    function_definition("function_definition");

x3::rule<external_declaration_tag, AST::ExternalDeclaration>
    external_declaration("external_declaration");

x3::rule<translation_unit_tag, AST::TranslationUnit>
    translation_unit("translation_unit");

} // namespace Grammar
} // namespace Parser

#endif
