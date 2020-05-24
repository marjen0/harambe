/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_HOME_MARIJUS_DOCUMENTS_KTU_2019_PKT2_BUILD_PARSER_HPP_INCLUDED
# define YY_YY_HOME_MARIJUS_DOCUMENTS_KTU_2019_PKT2_BUILD_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y"


# define YYLTYPE_IS_DECLARED 1 /* alert the parser that we have our own definition */


#line 54 "/home/marijus/Documents/KTU_2019_PKT2/build/parser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENTIFIER = 258,
    TINTEGER = 259,
    TDOUBLE = 260,
    TSTR = 261,
    TBOOL = 262,
    TCEQ = 263,
    TCNE = 264,
    TCLO = 265,
    TCLE = 266,
    TCGR = 267,
    TCGE = 268,
    TEQUAL = 269,
    TLTLT = 270,
    TCOMMA = 271,
    TDOT = 272,
    TCOLON = 273,
    TRANGE = 274,
    TLPAREN = 275,
    TRPAREN = 276,
    TLBRACKET = 277,
    TRBRACKET = 278,
    TPLUS = 279,
    TMINUS = 280,
    TMUL = 281,
    TDIV = 282,
    TNOT = 283,
    TAND = 284,
    TOR = 285,
    TIF = 286,
    TELSE = 287,
    TWHILE = 288,
    TTO = 289,
    TSQUOTE = 290,
    TDEF = 291,
    TRETURN = 292,
    TRETURN_SIMPLE = 293,
    TVAR = 294,
    IS = 295,
    TBLOCKSTART = 296,
    TBLOCKEND = 297,
    DEBUGSTART = 298,
    DEBUGEND = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 44 "parser.y"

			harambe::Node *node;
			harambe::Block *block;
			harambe::Expression *expr;
			harambe::Statement *stmt;
			harambe::Identifier *ident;
			harambe::VariableDeclaration *var_decl;
			harambe::VariableDeclarationDeduce *var_decl_deduce;
			std::vector<harambe::VariableDeclaration*> *varvec;
			std::vector<harambe::Expression*> *exprvec;
			std::string *string;
			int token;		
		

#line 125 "/home/marijus/Documents/KTU_2019_PKT2/build/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_HOME_MARIJUS_DOCUMENTS_KTU_2019_PKT2_BUILD_PARSER_HPP_INCLUDED  */
