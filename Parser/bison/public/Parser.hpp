// A Bison parser, made by GNU Bison 3.1.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file bison/public/Parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_BISON_PUBLIC_PARSER_HPP_INCLUDED
# define YY_YY_BISON_PUBLIC_PARSER_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 6 "bison/private/C.y" // lalr1.cc:395

#include "Parser/ASTNode.hpp"

#include <unordered_map>

#define YYDEBUG 1

using namespace Parser;

std::unique_ptr<ASTNode> make_identifier(
    std::string const &s, std::unordered_map<std::string, Token> &symbols);

#line 57 "bison/public/Parser.hpp" // lalr1.cc:395


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"


#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 141 "bison/public/Parser.hpp" // lalr1.cc:395



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {}

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;
  };


  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // unary_operator
      // pointer
      char dummy1[sizeof(Token)];

      // CONSTANT
      char dummy2[sizeof(int)];

      // IDENTIFIER
      // STRING_LITERAL
      char dummy3[sizeof(std::string)];

      // goal
      // primary_expression
      // postfix_expression
      // argument_expression_list
      // unary_expression
      // multiplicative_expression
      // additive_expression
      // relational_expression
      // equality_expression
      // assignment_expression
      // expression
      // declaration
      // declaration_specifiers
      // init_declarator_list
      // init_declarator
      // storage_class_specifier
      // type_specifier
      // declarator
      // direct_declarator
      // parameter_list
      // parameter_declaration
      // identifier_list
      // abstract_declarator
      // direct_abstract_declarator
      // statement
      // compound_statement
      // declaration_list
      // statement_list
      // expression_statement
      // selection_statement
      // iteration_statement
      // jump_statement
      // translation_unit
      // external_declaration
      // function_definition
      char dummy4[sizeof(std::unique_ptr<ASTNode>)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m);
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        IDENTIFIER = 258,
        STRING_LITERAL = 259,
        CONSTANT = 260,
        LE_OP = 261,
        GE_OP = 262,
        NE_OP = 263,
        EQ_OP = 264,
        EXTERN = 265,
        AUTO = 266,
        INT = 267,
        VOID = 268,
        FUNCTION = 269,
        APPLY = 270,
        LEAF = 271,
        IF = 272,
        ELSE = 273,
        WHILE = 274,
        CONTINUE = 275,
        BREAK = 276,
        RETURN = 277
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t);

  basic_symbol (typename Base::kind_type t, const Token& v);

  basic_symbol (typename Base::kind_type t, const int& v);

  basic_symbol (typename Base::kind_type t, const std::string& v);

  basic_symbol (typename Base::kind_type t, const std::unique_ptr<ASTNode>& v);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v);

    static inline
    symbol_type
    make_STRING_LITERAL (const std::string& v);

    static inline
    symbol_type
    make_CONSTANT (const int& v);

    static inline
    symbol_type
    make_LE_OP ();

    static inline
    symbol_type
    make_GE_OP ();

    static inline
    symbol_type
    make_NE_OP ();

    static inline
    symbol_type
    make_EQ_OP ();

    static inline
    symbol_type
    make_EXTERN ();

    static inline
    symbol_type
    make_AUTO ();

    static inline
    symbol_type
    make_INT ();

    static inline
    symbol_type
    make_VOID ();

    static inline
    symbol_type
    make_FUNCTION ();

    static inline
    symbol_type
    make_APPLY ();

    static inline
    symbol_type
    make_LEAF ();

    static inline
    symbol_type
    make_IF ();

    static inline
    symbol_type
    make_ELSE ();

    static inline
    symbol_type
    make_WHILE ();

    static inline
    symbol_type
    make_CONTINUE ();

    static inline
    symbol_type
    make_BREAK ();

    static inline
    symbol_type
    make_RETURN ();


    /// Build a parser object.
    parser (std::unique_ptr<ASTNode> tree_yyarg, std::unordered_map<std::string, Token> &symbols_yyarg);
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Copy construct (for efficiency).
      stack_symbol_type (const stack_symbol_type& that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 380,     ///< Last index in yytable_.
      yynnts_ = 38,  ///< Number of nonterminal symbols.
      yyfinal_ = 22, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 39  ///< Number of tokens.
    };


    // User arguments.
    std::unique_ptr<ASTNode> tree;
    std::unordered_map<std::string, Token> &symbols;
  };

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,    32,    26,     2,
      23,    24,    27,    28,    25,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      33,    35,    34,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
    };
    const unsigned user_token_number_max_ = 277;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    switch (other.type_get ())
    {
      case 45: // unary_operator
      case 60: // pointer
        value.copy< Token > (other.value);
        break;

      case 5: // CONSTANT
        value.copy< int > (other.value);
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.copy< std::string > (other.value);
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
        value.copy< std::unique_ptr<ASTNode> > (other.value);
        break;

      default:
        break;
    }

  }

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value ()
  {
    (void) v;
    switch (this->type_get ())
    {
      case 45: // unary_operator
      case 60: // pointer
        value.copy< Token > (v);
        break;

      case 5: // CONSTANT
        value.copy< int > (v);
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.copy< std::string > (v);
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
        value.copy< std::unique_ptr<ASTNode> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Token& v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int& v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string& v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::unique_ptr<ASTNode>& v)
    : Base (t)
    , value (v)
  {}


  template <typename Base>
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
  switch (yytype)
    {
      case 45: // unary_operator
      case 60: // pointer
        value.template destroy< Token > ();
        break;

      case 5: // CONSTANT
        value.template destroy< int > ();
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.template destroy< std::string > ();
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
        value.template destroy< std::unique_ptr<ASTNode> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 45: // unary_operator
      case 60: // pointer
        value.move< Token > (s.value);
        break;

      case 5: // CONSTANT
        value.move< int > (s.value);
        break;

      case 3: // IDENTIFIER
      case 4: // STRING_LITERAL
        value.move< std::string > (s.value);
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
        value.move< std::unique_ptr<ASTNode> > (s.value);
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }

  inline
  parser::token_type
  parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    40,    41,    44,    38,    42,    43,    45,
      33,    47,    37,    60,    62,    61,    59,   123,   125
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  parser::symbol_type
  parser::make_IDENTIFIER (const std::string& v)
  {
    return symbol_type (token::IDENTIFIER, v);
  }

  parser::symbol_type
  parser::make_STRING_LITERAL (const std::string& v)
  {
    return symbol_type (token::STRING_LITERAL, v);
  }

  parser::symbol_type
  parser::make_CONSTANT (const int& v)
  {
    return symbol_type (token::CONSTANT, v);
  }

  parser::symbol_type
  parser::make_LE_OP ()
  {
    return symbol_type (token::LE_OP);
  }

  parser::symbol_type
  parser::make_GE_OP ()
  {
    return symbol_type (token::GE_OP);
  }

  parser::symbol_type
  parser::make_NE_OP ()
  {
    return symbol_type (token::NE_OP);
  }

  parser::symbol_type
  parser::make_EQ_OP ()
  {
    return symbol_type (token::EQ_OP);
  }

  parser::symbol_type
  parser::make_EXTERN ()
  {
    return symbol_type (token::EXTERN);
  }

  parser::symbol_type
  parser::make_AUTO ()
  {
    return symbol_type (token::AUTO);
  }

  parser::symbol_type
  parser::make_INT ()
  {
    return symbol_type (token::INT);
  }

  parser::symbol_type
  parser::make_VOID ()
  {
    return symbol_type (token::VOID);
  }

  parser::symbol_type
  parser::make_FUNCTION ()
  {
    return symbol_type (token::FUNCTION);
  }

  parser::symbol_type
  parser::make_APPLY ()
  {
    return symbol_type (token::APPLY);
  }

  parser::symbol_type
  parser::make_LEAF ()
  {
    return symbol_type (token::LEAF);
  }

  parser::symbol_type
  parser::make_IF ()
  {
    return symbol_type (token::IF);
  }

  parser::symbol_type
  parser::make_ELSE ()
  {
    return symbol_type (token::ELSE);
  }

  parser::symbol_type
  parser::make_WHILE ()
  {
    return symbol_type (token::WHILE);
  }

  parser::symbol_type
  parser::make_CONTINUE ()
  {
    return symbol_type (token::CONTINUE);
  }

  parser::symbol_type
  parser::make_BREAK ()
  {
    return symbol_type (token::BREAK);
  }

  parser::symbol_type
  parser::make_RETURN ()
  {
    return symbol_type (token::RETURN);
  }



} // yy
#line 1336 "bison/public/Parser.hpp" // lalr1.cc:395




#endif // !YY_YY_BISON_PUBLIC_PARSER_HPP_INCLUDED
