#ifndef __ASTNODE_H
#define __ASTNODE_H

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

namespace Parser {
namespace AST {

namespace x3 = boost::spirit::x3;

struct AdditiveExpression;
struct AssignmentExpression;
struct DirectAbstractDeclarator;
struct DirectDeclarator;
struct EqualityExpression;
struct FunctionDefinition;
struct MultiplicativeExpression;
struct ParameterDeclaration;
struct RelationalExpression;
struct Statement;
struct StatementList;

using Expression = std::vector<x3::forward_ast<AssignmentExpression>>;
using PrimaryExpression =
    x3::variant<Expression, std::string *, std::string, int>;
using ArgumentExpressionList =
    std::vector<x3::forward_ast<AssignmentExpression>>;

struct PostfixExpression {
  PrimaryExpression expression;
  std::vector<ArgumentExpressionList> argument_lists;
};

enum class UnaryOperators {
  REFERENCE,
  DEREFERENCE,
  POSITIVE,
  NEGATIVE,
  INVERSION
};
struct UnaryExpression {
  std::vector<UnaryOperators> operators;
  PostfixExpression expression;
};

struct Multiplication {
  x3::forward_ast<MultiplicativeExpression> lhs;
  UnaryExpression rhs;
};

struct Division {
  x3::forward_ast<MultiplicativeExpression> lhs;
  UnaryExpression rhs;
};

struct Modulo {
  x3::forward_ast<MultiplicativeExpression> lhs;
  UnaryExpression rhs;
};

struct MultiplicativeExpression
    : x3::variant<UnaryExpression, Multiplication, Division, Modulo> {};

struct Addition {
  x3::forward_ast<AdditiveExpression> lhs;
  MultiplicativeExpression rhs;
};

struct Subtraction {
  x3::forward_ast<AdditiveExpression> lhs;
  MultiplicativeExpression rhs;
};

struct AdditiveExpression
    : x3::variant<MultiplicativeExpression, Addition, Subtraction> {};

struct LessThan {
  x3::forward_ast<RelationalExpression> lhs;
  AdditiveExpression rhs;
};

struct GreaterThan {
  x3::forward_ast<RelationalExpression> lhs;
  AdditiveExpression rhs;
};

struct LessThanOrEqualTo {
  x3::forward_ast<RelationalExpression> lhs;
  AdditiveExpression rhs;
};

struct GreaterThanOrEqualTo {
  x3::forward_ast<RelationalExpression> lhs;
  AdditiveExpression rhs;
};

struct RelationalExpression
    : x3::variant<AdditiveExpression, LessThan, GreaterThan, LessThanOrEqualTo,
                  GreaterThanOrEqualTo> {};

struct Equals {
  x3::forward_ast<EqualityExpression> lhs;
  RelationalExpression rhs;
};

struct NotEqual {
  x3::forward_ast<EqualityExpression> lhs;
  RelationalExpression rhs;
};

struct EqualityExpression
    : x3::variant<RelationalExpression, Equals, NotEqual> {};

struct Assignment {
  UnaryExpression lhs;
  x3::forward_ast<AssignmentExpression> rhs;
};

struct AssignmentExpression : x3::variant<EqualityExpression, Assignment> {};

enum class StorageClassSpecifier { AUTO, EXTERN };
enum class TypeSpecifier { VOID, INT, FUNCTION };

using DeclarationSpecifier = x3::variant<StorageClassSpecifier, TypeSpecifier>;
using Parameters = std::vector<x3::forward_ast<ParameterDeclaration>>;

struct DirectDeclarator {
  std::string *identifier;
  std::vector<x3::variant<Parameters, std::string *>>
      parameter_and_identifier_list;
};

struct Declarator {
  int pointer_depth;
  DirectDeclarator direct_declarator;
};

struct InitDeclarator {
  Declarator declarator;
  boost::optional<AssignmentExpression> expression;
};

struct AbstractDeclarator {
  int pointer_depth;
  boost::optional<x3::forward_ast<DirectAbstractDeclarator>> declarator;
};

struct DirectAbstractDeclarator {
  boost::optional<AbstractDeclarator> declarator;
  std::vector<Parameters> parameter_lists;
};

struct DeclaratorDeclaration {
  std::vector<DeclarationSpecifier> specifiers;
  std::vector<InitDeclarator> declarators;
};

struct ParameterDeclaration {
  std::vector<DeclarationSpecifier> specifiers;
  x3::variant<Declarator, AbstractDeclarator> declarator;
};

using Declaration =
    x3::variant<DeclaratorDeclaration, x3::forward_ast<FunctionDefinition>>;

struct If {
  Expression condition;
  x3::forward_ast<Statement> body;
};

struct IfElse {
  Expression condition;
  x3::forward_ast<Statement> if_body;
  x3::forward_ast<Statement> else_body;
};

struct While {
  Expression condition;
  x3::forward_ast<Statement> body;
};

using ReturnStatement = boost::optional<Expression>;

enum class JumpKeywords { CONTINUE, BREAK };
using JumpStatement = x3::variant<ReturnStatement, JumpKeywords>;

struct CompoundStatement {
  std::vector<Declaration> declarations;
  std::vector<x3::forward_ast<Statement>> statements;
};

struct Statement : x3::variant<CompoundStatement, Expression, If, IfElse, While,
                               JumpStatement> {};

struct FunctionDefinition {
  std::vector<DeclarationSpecifier> specifiers;
  Declarator declarator;
  std::vector<Declaration> declarations;
  CompoundStatement body;
};

using ExternalDeclaration = x3::variant<FunctionDefinition, Declaration>;
using TranslationUnit = std::vector<ExternalDeclaration>;

} // namespace AST
} // namespace Parser

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::PostfixExpression,
                          (Parser::AST::PrimaryExpression, expression),
                          (std::vector<Parser::AST::ArgumentExpressionList>,
                           argument_lists))

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::UnaryExpression, operators, expression)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Multiplication, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Division, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Modulo, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Addition, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Subtraction, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::LessThan, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::GreaterThan, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::LessThanOrEqualTo, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::GreaterThanOrEqualTo, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Equals, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::NotEqual, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Assignment, lhs, rhs)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::DirectDeclarator, identifier,
                          parameter_and_identifier_list)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::Declarator, pointer_depth,
                          direct_declarator)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::InitDeclarator, declarator, expression)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::AbstractDeclarator, pointer_depth,
                          declarator)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::DirectAbstractDeclarator, declarator,
                          parameter_lists)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::DeclaratorDeclaration, specifiers,
                          declarators)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::ParameterDeclaration, specifiers,
                          declarator)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::If, condition, body)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::IfElse, if_body, else_body)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::While, condition, body)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::CompoundStatement, declarations,
                          statements)

BOOST_FUSION_ADAPT_STRUCT(Parser::AST::FunctionDefinition, specifiers,
                          declarator, declarations, body)

#endif
