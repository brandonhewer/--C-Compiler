// A Bison parser, made by GNU Bison 3.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "bison/private/C.tab.cpp" // lalr1.cc:407

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.hpp"

// User implementation prologue.

#line 51 "bison/private/C.tab.cpp" // lalr1.cc:415


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 127 "bison/private/C.tab.cpp" // lalr1.cc:491

  /// Build a parser object.
  parser::parser (std::unique_ptr<ASTNode> tree_yyarg, std::unordered_map<std::string, Token> &symbols_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      tree (tree_yyarg),
      symbols (symbols_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state)
  {
    switch (that.type_get ())
    {
      case 45: // unary_operator
      case 60: // pointer
        value.copy< Token > (that.value);
        break;

      case 5: // CONSTANT
        value.copy< int > (that.value);
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.copy< std::string > (that.value);
        break;

      case 40: // goal
      case 41: // primary_expression
      case 42: // postfix_expression
      case 43: // argument_expression_list
      case 44: // unary_expression
      case 46: // multiplicative_expression
      case 47: // additive_expression
      case 48: // relational_expression
      case 49: // equality_expression
      case 50: // assignment_expression
      case 51: // expression
      case 52: // declaration
      case 53: // declaration_specifiers
      case 54: // init_declarator_list
      case 55: // init_declarator
      case 56: // storage_class_specifier
      case 57: // type_specifier
      case 58: // declarator
      case 59: // direct_declarator
      case 61: // parameter_list
      case 62: // parameter_declaration
      case 63: // identifier_list
      case 64: // abstract_declarator
      case 65: // direct_abstract_declarator
      case 66: // statement
      case 67: // compound_statement
      case 68: // declaration_list
      case 69: // statement_list
      case 70: // expression_statement
      case 71: // selection_statement
      case 72: // iteration_statement
      case 73: // jump_statement
      case 74: // translation_unit
      case 75: // external_declaration
      case 76: // function_definition
        value.copy< std::unique_ptr<ASTNode> > (that.value);
        break;

      default:
        break;
    }

  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      case 45: // unary_operator
      case 60: // pointer
        value.move< Token > (that.value);
        break;

      case 5: // CONSTANT
        value.move< int > (that.value);
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.move< std::string > (that.value);
        break;

      case 40: // goal
      case 41: // primary_expression
      case 42: // postfix_expression
      case 43: // argument_expression_list
      case 44: // unary_expression
      case 46: // multiplicative_expression
      case 47: // additive_expression
      case 48: // relational_expression
      case 49: // equality_expression
      case 50: // assignment_expression
      case 51: // expression
      case 52: // declaration
      case 53: // declaration_specifiers
      case 54: // init_declarator_list
      case 55: // init_declarator
      case 56: // storage_class_specifier
      case 57: // type_specifier
      case 58: // declarator
      case 59: // direct_declarator
      case 61: // parameter_list
      case 62: // parameter_declaration
      case 63: // identifier_list
      case 64: // abstract_declarator
      case 65: // direct_abstract_declarator
      case 66: // statement
      case 67: // compound_statement
      case 68: // declaration_list
      case 69: // statement_list
      case 70: // expression_statement
      case 71: // selection_statement
      case 72: // iteration_statement
      case 73: // jump_statement
      case 74: // translation_unit
      case 75: // external_declaration
      case 76: // function_definition
        value.move< std::unique_ptr<ASTNode> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 45: // unary_operator
      case 60: // pointer
        value.copy< Token > (that.value);
        break;

      case 5: // CONSTANT
        value.copy< int > (that.value);
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.copy< std::string > (that.value);
        break;

      case 40: // goal
      case 41: // primary_expression
      case 42: // postfix_expression
      case 43: // argument_expression_list
      case 44: // unary_expression
      case 46: // multiplicative_expression
      case 47: // additive_expression
      case 48: // relational_expression
      case 49: // equality_expression
      case 50: // assignment_expression
      case 51: // expression
      case 52: // declaration
      case 53: // declaration_specifiers
      case 54: // init_declarator_list
      case 55: // init_declarator
      case 56: // storage_class_specifier
      case 57: // type_specifier
      case 58: // declarator
      case 59: // direct_declarator
      case 61: // parameter_list
      case 62: // parameter_declaration
      case 63: // identifier_list
      case 64: // abstract_declarator
      case 65: // direct_abstract_declarator
      case 66: // statement
      case 67: // compound_statement
      case 68: // declaration_list
      case 69: // statement_list
      case 70: // expression_statement
      case 71: // selection_statement
      case 72: // iteration_statement
      case 73: // jump_statement
      case 74: // translation_unit
      case 75: // external_declaration
      case 76: // function_definition
        value.copy< std::unique_ptr<ASTNode> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (tree, symbols));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 45: // unary_operator
      case 60: // pointer
        yylhs.value.build< Token > ();
        break;

      case 5: // CONSTANT
        yylhs.value.build< int > ();
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        yylhs.value.build< std::string > ();
        break;

      case 40: // goal
      case 41: // primary_expression
      case 42: // postfix_expression
      case 43: // argument_expression_list
      case 44: // unary_expression
      case 46: // multiplicative_expression
      case 47: // additive_expression
      case 48: // relational_expression
      case 49: // equality_expression
      case 50: // assignment_expression
      case 51: // expression
      case 52: // declaration
      case 53: // declaration_specifiers
      case 54: // init_declarator_list
      case 55: // init_declarator
      case 56: // storage_class_specifier
      case 57: // type_specifier
      case 58: // declarator
      case 59: // direct_declarator
      case 61: // parameter_list
      case 62: // parameter_declaration
      case 63: // identifier_list
      case 64: // abstract_declarator
      case 65: // direct_abstract_declarator
      case 66: // statement
      case 67: // compound_statement
      case 68: // declaration_list
      case 69: // statement_list
      case 70: // expression_statement
      case 71: // selection_statement
      case 72: // iteration_statement
      case 73: // jump_statement
      case 74: // translation_unit
      case 75: // external_declaration
      case 76: // function_definition
        yylhs.value.build< std::unique_ptr<ASTNode> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 72 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 665 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 3:
#line 76 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_identifier(yystack_[0].value.as< std::string > (), symbols)); }
#line 671 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 4:
#line 77 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(yystack_[0].value.as< int > ())); }
#line 677 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 5:
#line 78 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(yystack_[0].value.as< std::string > ())); }
#line 683 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 6:
#line 79 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 689 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 7:
#line 83 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 695 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 8:
#line 85 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ())); 
      }
#line 703 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 9:
#line 89 "bison/private/C.y" // lalr1.cc:870
    {
			  std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::APPLY, std::move(yystack_[3].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); 
      }
#line 711 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 10:
#line 95 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 717 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 11:
#line 97 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::SEPARATE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); 
      }
#line 725 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 12:
#line 103 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 731 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 13:
#line 105 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(yystack_[1].value.as< Token > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()), nullptr)); 
      }
#line 739 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 14:
#line 111 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Operators::AMPERSAND; }
#line 745 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 15:
#line 112 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Operators::MULTIPLY; }
#line 751 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 16:
#line 113 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Operators::PLUS; }
#line 757 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 17:
#line 114 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Operators::MINUS; }
#line 763 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 18:
#line 115 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Operators::INVERSION; }
#line 769 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 19:
#line 119 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 775 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 20:
#line 121 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::MULTIPLY, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 783 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 21:
#line 125 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::DIVIDE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 791 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 22:
#line 129 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::MODULO, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 799 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 23:
#line 135 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 805 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 24:
#line 137 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::PLUS, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 813 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 25:
#line 141 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::MINUS, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 821 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 26:
#line 147 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 827 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 27:
#line 149 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Comparators::LESS_THAN, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 835 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 28:
#line 153 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Comparators::GREATER_THAN, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 843 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 29:
#line 157 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Comparators::LESS_THAN_OR_EQUAL_TO, 
                       std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 852 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 30:
#line 162 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Comparators::GREATER_THAN_OR_EQUAL_TO, 
                       std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 861 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 31:
#line 169 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 867 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 32:
#line 171 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::ASSIGNMENT, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 875 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 33:
#line 175 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Comparators::NOT_EQUAL, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 883 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 34:
#line 181 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 889 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 35:
#line 183 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Comparators::EQUALS, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 897 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 36:
#line 189 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 903 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 37:
#line 191 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::SEPARATE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 911 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 38:
#line 197 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 917 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 39:
#line 198 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 923 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 40:
#line 200 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 931 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 41:
#line 206 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 937 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 42:
#line 208 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::COMPOSE_TYPE_SPECIFIERS, 
                       std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 946 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 43:
#line 212 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 952 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 44:
#line 214 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::COMPOSE_TYPE_SPECIFIERS, 
                       std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 961 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 45:
#line 221 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 967 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 46:
#line 223 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::SEPARATE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 975 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 47:
#line 229 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 981 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 48:
#line 231 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::ASSIGNMENT, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 989 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 49:
#line 237 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::EXTERN)); }
#line 995 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 50:
#line 238 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::AUTO)); }
#line 1001 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 51:
#line 242 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::VOID)); }
#line 1007 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 52:
#line 243 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::INT)); }
#line 1013 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 53:
#line 244 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::FUNCTION)); }
#line 1019 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 54:
#line 249 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::POINTS_TO, std::move(yystack_[1].value.as< Token > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); 
      }
#line 1027 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 55:
#line 252 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1033 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 56:
#line 256 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(yystack_[0].value.as< std::string > ())); }
#line 1039 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 57:
#line 258 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); 
      }
#line 1047 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 58:
#line 262 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE_FUNCTION, 
                       std::move(yystack_[3].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1056 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 59:
#line 267 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE_FUNCTION, 
                       std::move(yystack_[3].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1065 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 60:
#line 272 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE_FUNCTION, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), nullptr)); 
      }
#line 1073 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 61:
#line 278 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Pointer{1}); }
#line 1079 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 62:
#line 279 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< Token > (), Pointer{yystack_[0].value.as< Token > ().depth}); }
#line 1085 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 63:
#line 283 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1091 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 64:
#line 285 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::SEPARATE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1099 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 65:
#line 292 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE, std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1107 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 66:
#line 296 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE, std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1115 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 67:
#line 299 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1121 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 68:
#line 303 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(yystack_[0].value.as< std::string > ())); }
#line 1127 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 69:
#line 305 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::SEPARATE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), make_node(yystack_[0].value.as< std::string > ()))); 
      }
#line 1135 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 70:
#line 311 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< Token > ())); }
#line 1141 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 71:
#line 312 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1147 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 72:
#line 314 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DECLARE_ABSTRACT, 
                                make_node(yystack_[1].value.as< Token > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1156 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 73:
#line 321 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1162 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 74:
#line 322 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), nullptr); }
#line 1168 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 75:
#line 323 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1174 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 76:
#line 325 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::APPLY, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), nullptr)); 
      }
#line 1182 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 77:
#line 329 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Operators::APPLY, std::move(yystack_[3].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1190 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 78:
#line 335 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1196 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 79:
#line 336 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1202 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 80:
#line 337 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1208 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 81:
#line 338 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1214 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 82:
#line 339 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1220 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 83:
#line 343 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), nullptr); }
#line 1226 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 84:
#line 344 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1232 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 85:
#line 345 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1238 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 86:
#line 347 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::COMPOUND_STATEMENTS, 
                       std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1247 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 87:
#line 354 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1253 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 88:
#line 356 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::COMPOUND_STATEMENTS, 
                       std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1262 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 89:
#line 363 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1268 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 90:
#line 365 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::COMPOUND_STATEMENTS, 
                       std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1277 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 91:
#line 372 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), nullptr); }
#line 1283 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 92:
#line 373 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1289 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 93:
#line 378 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::IF, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1297 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 94:
#line 382 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::IF, std::move(yystack_[4].value.as< std::unique_ptr<ASTNode> > ()), 
                       make_node(Keywords::ELSE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())))); 
      }
#line 1306 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 95:
#line 390 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::WHILE, std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1314 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 96:
#line 397 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::CONTINUE, nullptr, nullptr)); 
      }
#line 1322 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 97:
#line 401 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::BREAK, nullptr, nullptr)); 
      }
#line 1330 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 98:
#line 405 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::RETURN, nullptr, nullptr)); 
      }
#line 1338 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 99:
#line 409 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(Keywords::RETURN, std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), nullptr)); 
      }
#line 1346 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 100:
#line 415 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1352 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 101:
#line 417 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::ADD_TO_TRANSLATION_UNIT, 
                       std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ())));
      }
#line 1361 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 102:
#line 424 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1367 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 103:
#line 425 "bison/private/C.y" // lalr1.cc:870
    { std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), yystack_[0].value.as< std::unique_ptr<ASTNode> > ())); }
#line 1373 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 104:
#line 430 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DEFINE_FUNCTION, 
                       make_node(MetaOperators::DEFINE_FUNCTION_HEADER, std::move(yystack_[3].value.as< std::unique_ptr<ASTNode> > ()), 
                                 make_node(MetaOperators::DEFINE_FUNCTION_CALL_INTERFACE, 
                                           std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()))), 
                       std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1385 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 105:
#line 438 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DEFINE_FUNCTION, 
                       make_node(MetaOperators::DEFINE_FUNCTION_HEADER, 
                                 std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())), 
                       std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1396 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 106:
#line 445 "bison/private/C.y" // lalr1.cc:870
    {
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DEFINE_FUNCTION, 
                       make_node(MetaOperators::DEFINE_FUNCTION_HEADER, 
                                 std::move(yystack_[2].value.as< std::unique_ptr<ASTNode> > ()), std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ())), 
                       std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1407 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;

  case 107:
#line 452 "bison/private/C.y" // lalr1.cc:870
    { 
        std::swap(yylhs.value.as< std::unique_ptr<ASTNode> > (), make_node(MetaOperators::DEFINE_FUNCTION, std::move(yystack_[1].value.as< std::unique_ptr<ASTNode> > ()), 
                       std::move(yystack_[0].value.as< std::unique_ptr<ASTNode> > ()))); 
      }
#line 1416 "bison/private/C.tab.cpp" // lalr1.cc:870
    break;


#line 1420 "bison/private/C.tab.cpp" // lalr1.cc:870
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -112;

  const signed char parser::yytable_ninf_ = -57;

  const short
  parser::yypact_[] =
  {
     351,  -112,  -112,  -112,  -112,  -112,  -112,    22,    -8,    42,
    -112,    10,   210,   210,    17,     1,    13,   351,  -112,  -112,
      29,  -112,  -112,  -112,   -15,  -112,    71,  -112,  -112,   124,
    -112,  -112,    17,  -112,   356,     1,  -112,  -112,    22,  -112,
     301,  -112,    17,   258,  -112,  -112,    35,    56,    57,    69,
     273,   312,  -112,    -8,  -112,  -112,  -112,  -112,  -112,  -112,
      79,    51,   301,    93,   -11,     5,    24,  -112,    61,  -112,
    -112,   153,   181,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,    73,   115,  -112,   144,  -112,    75,  -112,   301,  -112,
    -112,  -112,   301,   301,  -112,  -112,  -112,    63,   163,   284,
     301,  -112,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,  -112,  -112,   209,  -112,  -112,   333,
    -112,    32,  -112,    89,  -112,   210,  -112,   111,   191,   219,
    -112,  -112,  -112,   224,  -112,  -112,  -112,  -112,  -112,  -112,
      93,    93,   -11,   -11,   -11,   -11,     5,     5,  -112,  -112,
    -112,   226,    97,    89,   182,  -112,  -112,   237,   237,  -112,
     301,  -112,  -112,  -112,   228,   105,  -112,  -112,  -112,   237,
    -112
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,    56,    49,    50,    52,    51,    53,     0,    61,     0,
     103,     0,    41,    43,     0,    55,     0,     2,   100,    39,
       0,    62,     1,    38,     0,    45,    47,    42,    44,     0,
      87,   107,     0,    39,     0,    54,   101,    57,     0,    40,
       0,   105,     0,     3,     5,     4,     0,     0,     0,     0,
       0,     0,    14,    15,    16,    17,    18,    91,    83,     7,
      12,    19,     0,    23,    26,    31,    34,    36,     0,    89,
      78,     0,     0,    79,    80,    81,    82,    88,   106,    68,
      60,    67,     0,    63,     0,    46,    47,     3,     0,    15,
      48,   104,     0,     0,    96,    97,    98,     0,     0,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    85,     0,    84,    90,     0,
      65,    70,    66,    71,    58,     0,    59,     0,     0,     0,
      99,     6,     8,     0,    10,    35,    20,    21,    22,    19,
      24,    25,    29,    30,    27,    28,    33,    32,    37,    86,
      74,     0,     0,    72,     0,    64,    69,     0,     0,     9,
       0,    75,    73,    76,     0,    93,    95,    11,    77,     0,
      94
  };

  const short
  parser::yypgoto_[] =
  {
    -112,  -112,  -112,  -112,  -112,   -39,  -112,    12,    23,    37,
    -112,   -38,   -36,     9,   -12,  -112,    88,  -112,  -112,    -4,
     -10,    -3,  -111,    30,  -112,    40,    50,   -68,    77,    66,
     106,  -112,  -112,  -112,  -112,  -112,   161,    87
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     9,    59,    60,   133,    61,    62,    63,    64,    65,
      66,    67,    68,    30,    11,    24,    25,    12,    13,    14,
      15,    16,    82,    83,    84,   122,   123,    69,    70,    32,
      72,    73,    74,    75,    76,    17,    18,    33
  };

  const short
  parser::yytable_[] =
  {
      27,    28,    90,    20,   118,    21,    35,    26,   151,    10,
      38,   107,   108,     1,    97,    98,     1,   105,   106,     8,
       1,    39,    81,   101,    34,     1,    10,     2,     3,     4,
       5,     6,   111,     7,    86,     1,     7,     8,   109,   110,
       7,    77,    22,   164,     8,     7,    23,    20,   118,     8,
      21,    77,    98,    37,    29,   119,   128,   129,    92,   112,
     100,   134,   135,   136,   137,   138,   139,   139,   139,   139,
     139,   139,   139,   139,     1,   148,     1,   120,   121,    93,
      77,     2,     3,     4,     5,     6,   113,    19,   113,   165,
     166,    31,    42,    94,     7,    71,   119,   114,     8,   130,
       8,   170,    99,    41,    19,    95,    40,    81,    29,    78,
      40,    35,   154,    81,   156,    20,   121,   140,   141,    91,
     102,   162,   167,   169,   103,   104,    85,    43,    44,    45,
     142,   143,   144,   145,     2,     3,     4,     5,     6,   124,
     125,    46,    81,    47,    48,    49,    50,    51,   146,   147,
      52,    53,    54,    55,    56,   155,    43,    44,    45,   152,
      57,    29,    58,     2,     3,     4,     5,     6,   126,   127,
      46,   153,    47,    48,    49,    50,    51,   116,    36,    52,
      53,    54,    55,    56,    87,    44,    45,   131,   113,    57,
      29,   115,     2,     3,     4,     5,     6,     0,    46,     0,
      47,    48,    49,    50,    88,     0,   163,    52,    89,    54,
      55,    56,    87,    44,    45,   157,   113,    57,    29,   117,
       2,     3,     4,     5,     6,     0,    46,     0,    47,    48,
      49,    50,    88,     0,     0,    52,    89,    54,    55,    56,
      87,    44,    45,   158,   113,    57,    29,   149,   159,   160,
     161,   125,   168,   125,    46,     0,    47,    48,    49,    50,
      88,   -56,     0,    52,    89,    54,    55,    56,   -56,   -56,
     -56,   -56,   -56,    57,    29,     0,    87,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,    87,    44,    45,
       0,     0,     0,     0,     0,   -56,    88,     0,     0,    52,
      89,    54,    55,    56,    87,    44,    45,    88,   132,    96,
      52,    89,    54,    55,    56,    43,    44,    45,     0,     0,
       0,     0,     0,     0,    88,     0,     0,    52,    89,    54,
      55,    56,     0,     0,     0,    51,     1,     0,    52,    53,
      54,    55,    56,     2,     3,     4,     5,     6,     0,     0,
       0,     0,     0,     0,     1,     0,   119,   150,     0,    79,
       8,     2,     3,     4,     5,     6,     2,     3,     4,     5,
       6,     0,     0,     0,     7,     0,     0,     0,     8,     0,
      80
  };

  const short
  parser::yycheck_[] =
  {
      12,    13,    40,     7,    72,     8,    16,    11,   119,     0,
      25,     6,     7,     3,    50,    51,     3,    28,    29,    27,
       3,    36,    34,    62,    23,     3,    17,    10,    11,    12,
      13,    14,     8,    23,    38,     3,    23,    27,    33,    34,
      23,    32,     0,   154,    27,    23,    36,    51,   116,    27,
      53,    42,    88,    24,    37,    23,    92,    93,    23,    35,
       9,    99,   100,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,     3,   113,     3,    81,    81,    23,
      71,    10,    11,    12,    13,    14,    25,     0,    25,   157,
     158,    14,    26,    36,    23,    29,    23,    36,    27,    36,
      27,   169,    23,    26,    17,    36,    35,   119,    37,    32,
      35,   121,    23,   125,     3,   119,   119,   105,   106,    42,
      27,    24,   160,    18,    31,    32,    38,     3,     4,     5,
     107,   108,   109,   110,    10,    11,    12,    13,    14,    24,
      25,    17,   154,    19,    20,    21,    22,    23,   111,   112,
      26,    27,    28,    29,    30,   125,     3,     4,     5,   119,
      36,    37,    38,    10,    11,    12,    13,    14,    24,    25,
      17,   121,    19,    20,    21,    22,    23,    71,    17,    26,
      27,    28,    29,    30,     3,     4,     5,    24,    25,    36,
      37,    38,    10,    11,    12,    13,    14,    -1,    17,    -1,
      19,    20,    21,    22,    23,    -1,    24,    26,    27,    28,
      29,    30,     3,     4,     5,    24,    25,    36,    37,    38,
      10,    11,    12,    13,    14,    -1,    17,    -1,    19,    20,
      21,    22,    23,    -1,    -1,    26,    27,    28,    29,    30,
       3,     4,     5,    24,    25,    36,    37,    38,    24,    25,
      24,    25,    24,    25,    17,    -1,    19,    20,    21,    22,
      23,     3,    -1,    26,    27,    28,    29,    30,    10,    11,
      12,    13,    14,    36,    37,    -1,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    37,    23,    -1,    -1,    26,
      27,    28,    29,    30,     3,     4,     5,    23,    24,    36,
      26,    27,    28,    29,    30,     3,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    23,     3,    -1,    26,    27,
      28,    29,    30,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    23,    24,    -1,     3,
      27,    10,    11,    12,    13,    14,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    23,    -1,    -1,    -1,    27,    -1,
      24
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,    10,    11,    12,    13,    14,    23,    27,    40,
      52,    53,    56,    57,    58,    59,    60,    74,    75,    76,
      58,    60,     0,    36,    54,    55,    58,    53,    53,    37,
      52,    67,    68,    76,    23,    59,    75,    24,    25,    36,
      35,    67,    68,     3,     4,     5,    17,    19,    20,    21,
      22,    23,    26,    27,    28,    29,    30,    36,    38,    41,
      42,    44,    45,    46,    47,    48,    49,    50,    51,    66,
      67,    68,    69,    70,    71,    72,    73,    52,    67,     3,
      24,    53,    61,    62,    63,    55,    58,     3,    23,    27,
      50,    67,    23,    23,    36,    36,    36,    51,    51,    23,
       9,    44,    27,    31,    32,    28,    29,     6,     7,    33,
      34,     8,    35,    25,    36,    38,    69,    38,    66,    23,
      58,    60,    64,    65,    24,    25,    24,    25,    51,    51,
      36,    24,    24,    43,    50,    50,    44,    44,    44,    44,
      46,    46,    47,    47,    47,    47,    48,    48,    50,    38,
      24,    61,    64,    65,    23,    62,     3,    24,    24,    24,
      25,    24,    24,    24,    61,    66,    66,    50,    24,    18,
      66
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    39,    40,    41,    41,    41,    41,    42,    42,    42,
      43,    43,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    46,    46,    47,    47,    47,    48,    48,    48,    48,
      48,    49,    49,    49,    50,    50,    51,    51,    52,    52,
      52,    53,    53,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    60,    60,    61,    61,    62,    62,    62,    63,    63,
      64,    64,    64,    65,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    67,    67,    67,    67,    68,    68,    69,
      69,    70,    70,    71,    71,    72,    73,    73,    73,    73,
      74,    74,    75,    75,    76,    76,    76,    76
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     3,     1,     3,     4,
       1,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     2,     1,
       3,     1,     2,     1,     2,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     2,     1,     1,     3,     4,     4,
       3,     1,     2,     1,     3,     2,     2,     1,     1,     3,
       1,     1,     2,     3,     2,     3,     3,     4,     1,     1,
       1,     1,     1,     2,     3,     3,     4,     1,     2,     1,
       2,     1,     2,     5,     7,     5,     2,     2,     2,     3,
       1,     2,     1,     1,     4,     3,     3,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "IDENTIFIER", "STRING_LITERAL",
  "CONSTANT", "LE_OP", "GE_OP", "NE_OP", "EQ_OP", "EXTERN", "AUTO", "INT",
  "VOID", "FUNCTION", "APPLY", "LEAF", "IF", "ELSE", "WHILE", "CONTINUE",
  "BREAK", "RETURN", "'('", "')'", "','", "'&'", "'*'", "'+'", "'-'",
  "'!'", "'/'", "'%'", "'<'", "'>'", "'='", "';'", "'{'", "'}'", "$accept",
  "goal", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "assignment_expression",
  "expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "declarator", "direct_declarator", "pointer",
  "parameter_list", "parameter_declaration", "identifier_list",
  "abstract_declarator", "direct_abstract_declarator", "statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", YY_NULLPTR
  };


  const unsigned short
  parser::yyrline_[] =
  {
       0,    72,    72,    76,    77,    78,    79,    83,    84,    88,
      95,    96,   103,   104,   111,   112,   113,   114,   115,   119,
     120,   124,   128,   135,   136,   140,   147,   148,   152,   156,
     161,   169,   170,   174,   181,   182,   189,   190,   197,   198,
     199,   206,   207,   212,   213,   221,   222,   229,   230,   237,
     238,   242,   243,   244,   248,   252,   256,   257,   261,   266,
     271,   278,   279,   283,   284,   291,   295,   299,   303,   304,
     311,   312,   313,   321,   322,   323,   324,   328,   335,   336,
     337,   338,   339,   343,   344,   345,   346,   354,   355,   363,
     364,   372,   373,   377,   381,   389,   396,   400,   404,   408,
     415,   416,   424,   425,   429,   437,   444,   451
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1871 "bison/private/C.tab.cpp" // lalr1.cc:1181
#line 457 "bison/private/C.y" // lalr1.cc:1182

#include <stdio.h>

extern char yytext[];
extern int column;

int yyerror(char *s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

Identifier const *
get_or_insert_symbol(std::string const &symbol,
                     std::unordered_map<std::string, Identifier> &symbols) {
  auto symbolIt = symbols.find(s);
  if (symbols.end() != symbolIt)
    return &symbolIt.second;
  return &(symbols[symbol] = Identifier{symbol});
}

std::unique_ptr<ASTNode>
make_identifier(std::string const &symbol,
                std::unordered_map<std::string, Token> &symbols) {
  return std::make_unique<ASTNode>(get_or_insert_symbol(symbol, symbols));
}



