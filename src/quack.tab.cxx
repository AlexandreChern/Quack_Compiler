// A Bison parser, made by GNU Bison 3.4.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "quack.tab.hxx"


// Unqualified %code blocks.
#line 24 "quack.yxx"

    #include "lex.yy.h"
    #undef yylex
    #define yylex lexer.yylex  /* Within bison's parse() we should invoke lexer.yylex(), not the global yylex() */
    void dump(AST::ASTNode* n);

#line 52 "quack.tab.cxx"


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


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
#line 143 "quack.tab.cxx"


  /// Build a parser object.
  parser::parser (yy::Lexer& lexer_yyarg, AST::ASTNode** root_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      root (root_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
    , location (std::move (that.location))
  {}
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
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
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
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
  parser::operator() ()
  {
    return parse ();
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

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
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
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
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
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
#line 134 "quack.yxx"
    { (yylhs.value.node) = new AST::Program(*(yystack_[1].value.classes), *(yystack_[0].value.block));
          // std::cerr << "Transmitting root to driver\n";
          *root = (yylhs.value.node); // Transmit tree back to driver
          // std::cerr << "Transmitted root to driver\n";
        }
#line 592 "quack.tab.cxx"
    break;

  case 3:
#line 140 "quack.yxx"
    {  (yylhs.value.classes) = new AST::Classes(); }
#line 598 "quack.tab.cxx"
    break;

  case 4:
#line 141 "quack.yxx"
    { (yylhs.value.classes) = (yystack_[1].value.classes); (yylhs.value.classes)->append((yystack_[0].value.cls));}
#line 604 "quack.tab.cxx"
    break;

  case 5:
#line 145 "quack.yxx"
    { AST::Ident* dummy = new AST::Ident("Obj");
          AST::Method* constructor = new AST::Method(*(yystack_[7].value.ident), *(yystack_[5].value.formals), *(yystack_[7].value.ident), *(yystack_[2].value.block));
          (yylhs.value.cls) = new AST::Class(*(yystack_[7].value.ident), *dummy, *constructor, *(yystack_[1].value.methods)); }
#line 612 "quack.tab.cxx"
    break;

  case 6:
#line 149 "quack.yxx"
    { (yylhs.value.cls) = new AST::Class(*(yystack_[9].value.ident), *(yystack_[4].value.ident), *(new AST::Method(*(yystack_[9].value.ident), *(yystack_[7].value.formals), *(yystack_[9].value.ident), *(yystack_[2].value.block))), *(yystack_[1].value.methods)); }
#line 618 "quack.tab.cxx"
    break;

  case 7:
#line 152 "quack.yxx"
    { (yylhs.value.methods) = new AST::Methods(); }
#line 624 "quack.tab.cxx"
    break;

  case 8:
#line 153 "quack.yxx"
    { (yylhs.value.methods) = (yystack_[1].value.methods); (yylhs.value.methods)->append((yystack_[0].value.method));}
#line 630 "quack.tab.cxx"
    break;

  case 9:
#line 157 "quack.yxx"
    { AST::Ident* dummy = new AST::Ident("Nothing");
          (yylhs.value.method) = new AST::Method(*(yystack_[4].value.ident), *(yystack_[2].value.formals), *dummy, *(yystack_[0].value.block));
        }
#line 638 "quack.tab.cxx"
    break;

  case 10:
#line 161 "quack.yxx"
    { (yylhs.value.method) = new AST::Method(*(yystack_[6].value.ident), *(yystack_[4].value.formals), *(yystack_[1].value.ident), *(yystack_[0].value.block)); }
#line 644 "quack.tab.cxx"
    break;

  case 11:
#line 164 "quack.yxx"
    { (yylhs.value.formals) = new AST::Formals(); }
#line 650 "quack.tab.cxx"
    break;

  case 12:
#line 165 "quack.yxx"
    { (yylhs.value.formals) = (yystack_[0].value.formals); }
#line 656 "quack.tab.cxx"
    break;

  case 13:
#line 169 "quack.yxx"
    { (yylhs.value.formals) = (yystack_[2].value.formals);
                (yylhs.value.formals)->append((yystack_[0].value.formal));
              }
#line 664 "quack.tab.cxx"
    break;

  case 14:
#line 173 "quack.yxx"
    { (yylhs.value.formals) = new AST::Formals();
              (yylhs.value.formals)->append((yystack_[0].value.formal)); 
            }
#line 672 "quack.tab.cxx"
    break;

  case 15:
#line 177 "quack.yxx"
    { (yylhs.value.formal) = new AST::Formal(*(yystack_[2].value.ident), *(yystack_[0].value.ident)); }
#line 678 "quack.tab.cxx"
    break;

  case 16:
#line 180 "quack.yxx"
    { (yylhs.value.block) = (yystack_[1].value.block); (yylhs.value.block)->append((yystack_[0].value.statement)); }
#line 684 "quack.tab.cxx"
    break;

  case 17:
#line 181 "quack.yxx"
    { (yylhs.value.block) = new AST::Block(); }
#line 690 "quack.tab.cxx"
    break;

  case 18:
#line 185 "quack.yxx"
    {  (yylhs.value.block) = (yystack_[1].value.block); }
#line 696 "quack.tab.cxx"
    break;

  case 19:
#line 194 "quack.yxx"
    { (yylhs.value.statement) = new AST::If(*(yystack_[2].value.expr), *(yystack_[1].value.block), *(yystack_[0].value.block)); }
#line 702 "quack.tab.cxx"
    break;

  case 20:
#line 198 "quack.yxx"
    { (yylhs.value.block) = new AST::Block();
               (yylhs.value.block)->append(new AST::If(*(yystack_[2].value.expr), *(yystack_[1].value.block), *(yystack_[0].value.block)));
             }
#line 710 "quack.tab.cxx"
    break;

  case 21:
#line 202 "quack.yxx"
    { (yylhs.value.block) = (yystack_[0].value.block); }
#line 716 "quack.tab.cxx"
    break;

  case 22:
#line 204 "quack.yxx"
    { (yylhs.value.block) = new AST::Block(); }
#line 722 "quack.tab.cxx"
    break;

  case 23:
#line 208 "quack.yxx"
    { (yylhs.value.statement) = new AST::While(*(yystack_[1].value.expr), *(yystack_[0].value.block));}
#line 728 "quack.tab.cxx"
    break;

  case 24:
#line 216 "quack.yxx"
    { (yylhs.value.statement) = new AST::Assign(*(yystack_[3].value.l_expr), *(yystack_[1].value.expr)); }
#line 734 "quack.tab.cxx"
    break;

  case 25:
#line 220 "quack.yxx"
    { (yylhs.value.statement) = new AST::AssignDeclare(*(yystack_[5].value.l_expr), *(yystack_[1].value.expr), *(yystack_[3].value.ident));}
#line 740 "quack.tab.cxx"
    break;

  case 26:
#line 227 "quack.yxx"
    { (yylhs.value.statement) = (yystack_[1].value.expr); }
#line 746 "quack.tab.cxx"
    break;

  case 28:
#line 232 "quack.yxx"
    { AST::Ident* dummy = new AST::Ident("Nothing");
            (yylhs.value.statement) = new AST::Return(*dummy); }
#line 753 "quack.tab.cxx"
    break;

  case 29:
#line 235 "quack.yxx"
    { (yylhs.value.statement) = new AST::Return(*(yystack_[1].value.expr)); }
#line 759 "quack.tab.cxx"
    break;

  case 30:
#line 239 "quack.yxx"
    { (yylhs.value.statement) = new AST::Typecase(*(yystack_[3].value.expr), *(yystack_[1].value.type_alternatives)); }
#line 765 "quack.tab.cxx"
    break;

  case 31:
#line 242 "quack.yxx"
    { (yylhs.value.type_alternatives) = new AST::Type_Alternatives(); }
#line 771 "quack.tab.cxx"
    break;

  case 32:
#line 244 "quack.yxx"
    { (yylhs.value.type_alternatives) = (yystack_[1].value.type_alternatives);
                      (yylhs.value.type_alternatives)->append((yystack_[0].value.type_alternative));
                    }
#line 779 "quack.tab.cxx"
    break;

  case 33:
#line 248 "quack.yxx"
    { (yylhs.value.type_alternatives) = new AST::Type_Alternatives();
                      (yylhs.value.type_alternatives)->append((yystack_[0].value.type_alternative));
                    }
#line 787 "quack.tab.cxx"
    break;

  case 34:
#line 254 "quack.yxx"
    { (yylhs.value.type_alternative) = new AST::Type_Alternative(*(yystack_[3].value.ident), *(yystack_[1].value.ident), *(yystack_[0].value.block)); }
#line 793 "quack.tab.cxx"
    break;

  case 35:
#line 265 "quack.yxx"
    { (yylhs.value.l_expr) =  new AST::Ident((yystack_[0].value.str)); }
#line 799 "quack.tab.cxx"
    break;

  case 36:
#line 267 "quack.yxx"
    { (yylhs.value.l_expr) = new AST::Dot(*(yystack_[2].value.expr), *(yystack_[0].value.ident)); }
#line 805 "quack.tab.cxx"
    break;

  case 37:
#line 282 "quack.yxx"
    { (yylhs.value.expr) = new AST::Load(*(yystack_[0].value.l_expr)); }
#line 811 "quack.tab.cxx"
    break;

  case 38:
#line 286 "quack.yxx"
    { (yylhs.value.expr) = new AST::StrConst((yystack_[0].value.str)); }
#line 817 "quack.tab.cxx"
    break;

  case 39:
#line 287 "quack.yxx"
    { (yylhs.value.expr) = new AST::IntConst((yystack_[0].value.num)); }
#line 823 "quack.tab.cxx"
    break;

  case 40:
#line 297 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("TIMES", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 829 "quack.tab.cxx"
    break;

  case 41:
#line 298 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("PLUS", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 835 "quack.tab.cxx"
    break;

  case 42:
#line 299 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("MINUS", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 841 "quack.tab.cxx"
    break;

  case 43:
#line 300 "quack.yxx"
    {
                              auto zero = new AST::IntConst(0);
                              (yylhs.value.expr) = AST::Call::binop("MINUS", *zero, *(yystack_[0].value.expr));
                            }
#line 850 "quack.tab.cxx"
    break;

  case 44:
#line 305 "quack.yxx"
    { (yylhs.value.expr) = (yystack_[1].value.expr); }
#line 856 "quack.tab.cxx"
    break;

  case 45:
#line 309 "quack.yxx"
    { (yylhs.value.expr) = new AST::And(*(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 862 "quack.tab.cxx"
    break;

  case 46:
#line 310 "quack.yxx"
    { (yylhs.value.expr) = new AST::Or(*(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 868 "quack.tab.cxx"
    break;

  case 47:
#line 311 "quack.yxx"
    { (yylhs.value.expr) = new AST::Not(*(yystack_[0].value.expr)); }
#line 874 "quack.tab.cxx"
    break;

  case 48:
#line 312 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("EQUALS", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 880 "quack.tab.cxx"
    break;

  case 49:
#line 313 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("ATMOST", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 886 "quack.tab.cxx"
    break;

  case 50:
#line 314 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("<", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 892 "quack.tab.cxx"
    break;

  case 51:
#line 315 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop("ATLEAST", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 898 "quack.tab.cxx"
    break;

  case 52:
#line 316 "quack.yxx"
    { (yylhs.value.expr) = AST::Call::binop(">", *(yystack_[2].value.expr), *(yystack_[0].value.expr)); }
#line 904 "quack.tab.cxx"
    break;

  case 53:
#line 335 "quack.yxx"
    { (yylhs.value.expr) = new AST::Call(*(yystack_[5].value.expr), *(yystack_[3].value.ident), *(yystack_[1].value.actuals)); }
#line 910 "quack.tab.cxx"
    break;

  case 54:
#line 338 "quack.yxx"
    { (yylhs.value.actuals) = new AST::Actuals(); }
#line 916 "quack.tab.cxx"
    break;

  case 55:
#line 339 "quack.yxx"
    { (yylhs.value.actuals) = (yystack_[0].value.actuals); }
#line 922 "quack.tab.cxx"
    break;

  case 56:
#line 342 "quack.yxx"
    { (yylhs.value.actuals) = (yystack_[2].value.actuals); (yylhs.value.actuals)->append((yystack_[0].value.expr)); }
#line 928 "quack.tab.cxx"
    break;

  case 57:
#line 343 "quack.yxx"
    { (yylhs.value.actuals) = new AST::Actuals(); (yylhs.value.actuals)->append((yystack_[0].value.expr)); }
#line 934 "quack.tab.cxx"
    break;

  case 58:
#line 347 "quack.yxx"
    { (yylhs.value.expr) = new AST::Construct(*(yystack_[3].value.ident), *(yystack_[1].value.actuals)); }
#line 940 "quack.tab.cxx"
    break;

  case 59:
#line 349 "quack.yxx"
    { (yylhs.value.ident) = new AST::Ident((yystack_[0].value.str)); }
#line 946 "quack.tab.cxx"
    break;


#line 950 "quack.tab.cxx"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -54;

  const signed char parser::yytable_ninf_ = -60;

  const short
  parser::yypact_[] =
  {
     -54,    19,    23,   -54,    14,   -54,   178,   -54,     9,     8,
     358,   358,   260,   358,   358,    18,   -54,   -54,   358,   358,
     -54,   -17,   196,    27,    14,   -54,   -54,    37,    37,   -54,
     213,    70,   314,    20,   278,    14,   358,   358,   358,   358,
     358,   358,   358,   358,   358,   358,   358,    14,   -54,   358,
      16,    29,   -54,    31,   -54,    22,   -54,   -54,    14,   -54,
      32,   230,   346,   331,    17,   314,   314,   331,   346,   -16,
     -16,    20,    40,   297,    36,    38,     6,    14,    14,   141,
     358,    44,   -54,   -15,   -54,    43,   358,   -54,   358,   -54,
     358,    14,   -54,   -54,   -54,   -54,    37,   -54,   -54,   -54,
      14,   247,    41,   297,    47,     4,    22,    44,   -54,   -54,
     -54,     2,   -54,   -54,     4,    14,   -54,   -54,     3,    51,
     -54,    14,    58,    -6,    14,   -54,    44,   -54
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,    17,     1,     0,     4,     0,    59,     0,     0,
       0,     0,     0,     0,     0,    35,    39,    38,     0,     0,
      16,    37,     0,     0,    11,    27,    37,     0,     0,    28,
       0,     0,    47,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    54,
       0,    12,    14,     0,    17,    22,    23,    29,    31,    44,
       0,     0,    51,    49,    48,    45,    46,    52,    50,    41,
      42,    40,    36,    57,     0,    55,     0,     0,     0,     0,
       0,     0,    19,     0,    33,     0,     0,    24,    54,    58,
       0,     0,    17,    13,    15,    18,     0,    21,    30,    32,
       0,     0,     0,    56,     0,     0,    22,     0,    25,    53,
      17,     0,    20,    34,     0,     0,     5,     8,     0,     0,
       6,    11,     0,     0,     0,     9,     0,    10
  };

  const signed char
  parser::yypgoto_[] =
  {
     -54,   -54,   -54,   -54,   -25,   -54,   -31,   -54,    25,   -53,
     -26,   -54,    -7,   -54,    21,    -2,    95,    28,   -54,    -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     5,   111,   117,    50,    51,    52,     6,
      55,    20,    82,    83,    84,    26,    22,    74,    75,    23
  };

  const signed char
  parser::yytable_[] =
  {
       8,    79,    56,     7,    21,     9,   115,   115,    -7,    46,
      10,    91,    47,    11,    12,    13,    35,    98,    36,     3,
      53,    14,    15,    16,    17,    54,     4,   124,    18,    80,
      81,    60,     7,    19,   116,   120,    -7,    92,    24,   105,
      44,    45,    46,    72,    25,    47,    76,   -59,    47,    37,
      38,    39,    40,    41,    85,    97,    49,   114,    42,    43,
      44,    45,    46,    77,    78,    47,    89,    86,    54,    88,
     106,   109,    90,    53,    94,    54,   100,    21,   110,    85,
     121,   113,    37,    38,    39,    40,    41,   104,   123,   118,
     122,    42,    43,    44,    45,    46,   107,   125,    47,   112,
     127,    58,    93,    21,    99,    27,    28,    30,    31,    32,
       0,   119,    21,    33,    34,     0,   102,    53,     0,     0,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,     9,     0,    73,     0,     0,    10,     0,     0,
      11,    12,    13,     0,     0,     0,     0,     0,    14,    15,
      16,    17,     0,     0,     0,    18,     0,     0,     0,     0,
      19,     0,     0,    95,     0,    96,     0,     0,    -2,     9,
       0,   101,     0,    73,    10,   103,     0,    11,    12,    13,
       0,     0,     0,     0,     0,    14,    15,    16,    17,     0,
       0,     0,    18,     0,     0,     0,     0,    19,    37,    38,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
      45,    46,     0,     0,    47,    37,    38,    39,    40,    41,
       0,     0,    48,     0,    42,    43,    44,    45,    46,     0,
       0,    47,    37,    38,    39,    40,    41,     0,     0,    57,
       0,    42,    43,    44,    45,    46,     0,     0,    47,    37,
      38,    39,    40,    41,     0,     0,    87,     0,    42,    43,
      44,    45,    46,     0,     0,    47,     0,    14,    15,    16,
      17,     0,     0,   108,    18,     0,     0,     0,     0,    19,
      37,    38,    39,    40,    41,     0,    29,     0,     0,    42,
      43,    44,    45,    46,     0,     0,    47,     0,    59,    37,
      38,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,    45,    46,     0,     0,    47,    37,    38,    39,     0,
       0,     0,     0,     0,     0,    42,    43,    44,    45,    46,
       0,     0,    47,    37,   -60,    39,     0,     0,     0,     0,
       0,     0,   -60,    43,    44,    45,    46,     0,   -60,    47,
      39,     0,     0,     0,     0,     0,     0,     0,   -60,    44,
      45,    46,     0,     0,    47,    14,    15,    16,    17,     0,
       0,     0,    18,     0,     0,     0,     0,    19
  };

  const signed char
  parser::yycheck_[] =
  {
       4,    54,    28,    18,     6,     1,     4,     4,     4,    25,
       6,     5,    28,     9,    10,    11,    33,    32,    35,     0,
      24,    17,    18,    19,    20,    31,     3,    33,    24,     7,
       8,    35,    18,    29,    32,    32,    32,    31,    29,    92,
      23,    24,    25,    47,    36,    28,    30,    29,    28,    12,
      13,    14,    15,    16,    58,    81,    29,   110,    21,    22,
      23,    24,    25,    34,    33,    28,    30,    35,    31,    29,
      96,    30,    34,    77,    78,    31,    33,    79,    31,    83,
      29,   107,    12,    13,    14,    15,    16,    91,    30,   114,
     121,    21,    22,    23,    24,    25,   100,   123,    28,   106,
     126,    31,    77,   105,    83,    10,    11,    12,    13,    14,
      -1,   115,   114,    18,    19,    -1,    88,   121,    -1,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     1,    -1,    49,    -1,    -1,     6,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    32,    -1,    80,    -1,    -1,     0,     1,
      -1,    86,    -1,    88,     6,    90,    -1,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    12,    13,    14,    15,    16,
      -1,    -1,    36,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    12,    13,    14,    15,    16,    -1,    -1,    36,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    12,
      13,    14,    15,    16,    -1,    -1,    36,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    -1,    17,    18,    19,
      20,    -1,    -1,    36,    24,    -1,    -1,    -1,    -1,    29,
      12,    13,    14,    15,    16,    -1,    36,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    -1,    30,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    12,    28,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    17,    18,    19,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    38,    39,     0,     3,    40,    46,    18,    56,     1,
       6,     9,    10,    11,    17,    18,    19,    20,    24,    29,
      48,    52,    53,    56,    29,    36,    52,    53,    53,    36,
      53,    53,    53,    53,    53,    33,    35,    12,    13,    14,
      15,    16,    21,    22,    23,    24,    25,    28,    36,    29,
      43,    44,    45,    56,    31,    47,    47,    36,    31,    30,
      56,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    56,    53,    54,    55,    30,    34,    33,    46,
       7,     8,    49,    50,    51,    56,    35,    36,    29,    30,
      34,     5,    31,    45,    56,    32,    53,    47,    32,    51,
      33,    53,    54,    53,    56,    46,    47,    56,    36,    30,
      31,    41,    49,    47,    46,     4,    32,    42,    41,    56,
      32,    29,    43,    30,    33,    47,    56,    47
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    37,    38,    39,    39,    40,    40,    41,    41,    42,
      42,    43,    43,    44,    44,    45,    46,    46,    47,    48,
      49,    49,    49,    48,    48,    48,    48,    48,    48,    48,
      48,    50,    50,    50,    51,    52,    52,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    53,    56
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     9,    11,     0,     2,     6,
       8,     0,     1,     3,     1,     3,     2,     0,     3,     4,
       4,     2,     0,     3,     4,     6,     2,     2,     2,     3,
       5,     0,     2,     1,     4,     1,     3,     1,     1,     1,
       3,     3,     3,     2,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     6,     0,     1,     3,     1,     4,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "CLASS", "DEF", "EXTENDS", "IF", "ELIF",
  "ELSE", "WHILE", "RETURN", "TYPECASE", "ATLEAST", "ATMOST", "EQUALS",
  "AND", "OR", "NOT", "IDENT", "INT_LIT", "STRING_LIT", "'>'", "'<'",
  "'+'", "'-'", "'*'", "'/'", "NEG", "'.'", "'('", "')'", "'{'", "'}'",
  "':'", "','", "'='", "';'", "$accept", "pgm", "classes", "class",
  "methods", "method", "formal_args", "formal_args_nonempty", "formal_arg",
  "statements", "statement_block", "statement", "opt_elif_parts",
  "type_alternatives", "type_alternative", "l_expr", "expr", "actual_args",
  "actual_args_nonempty", "ident", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  parser::yyrline_[] =
  {
       0,   133,   133,   140,   141,   144,   148,   152,   153,   156,
     160,   164,   165,   168,   172,   177,   180,   181,   185,   193,
     197,   201,   204,   207,   215,   219,   227,   228,   231,   234,
     238,   242,   243,   247,   253,   265,   267,   282,   286,   287,
     297,   298,   299,   300,   305,   309,   310,   311,   312,   313,
     314,   315,   316,   334,   338,   339,   342,   343,   347,   349
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

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,    25,    23,    34,    24,    28,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    36,
      22,    35,    21,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    27
    };
    const unsigned user_token_number_max_ = 276;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

} // yy
#line 1422 "quack.tab.cxx"

#line 350 "quack.yxx"


void yy::parser::error(const location_type& loc, const std::string& msg)
{
  report::error_at(loc, msg);
}
