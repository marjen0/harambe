%code requires {

# define YYLTYPE_IS_DECLARED 1 /* alert the parser that we have our own definition */

}

%{
    #include "AstNode.h"
	#include "FunctionDeclaration.h"
	#include "ClassDeclaration.h"
    #include <stdio.h>
    harambe::Block *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    int yyerror(char const * s );
    #define YYERROR_VERBOSE
    #define YYDEBUG 1

    extern std::stack<std::string> fileNames;

    # define YYLLOC_DEFAULT(Current, Rhs, N)                            \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
          (Current).file_name = fileNames.top();            		\
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
          (Current).file_name = fileNames.top();            		\
        }                                                               \
    while (0)

%}

/* Represents the many different ways we can access our data */
%union 		{
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
		}

/* 
Define our terminal symbols (tokens). This should match our tokens.l lex file. We also define the node type they represent.
*/
%token		<string> TIDENTIFIER TINTEGER TDOUBLE TSTR TBOOL
%token 		<token> TCEQ TCNE TCLO TCLE TCGR TCGE TEQUAL TLTLT
%token 		<token> TCOMMA TDOT TCOLON TRANGE
%token 		<token> TLPAREN TRPAREN TLBRACKET TRBRACKET
%token 		<token> TPLUS TMINUS TMUL TDIV
%token 		<token> TNOT TAND TOR
%token 		<token> TIF TELSE TWHILE TTO 
%token 		<token> TSQUOTE TDEF TRETURN TRETURN_SIMPLE TVAR IS
%token 		<token> TBLOCKSTART TBLOCKEND DEBUGSTART DEBUGEND

/* 
Define the type of node our nonterminal symbols represent. The types refer to the %union declaration above. Ex: when we call an ident (defined by union type ident) we are really calling an (Identifier*). It makes the compiler happy.
*/
%type 		<ident> ident
%type 		<expr> literals expr boolean_expr binop_expr unaryop_expr array_expr array_access range_expr
%type 		<varvec> func_decl_args
%type 		<exprvec> call_args array_elemets_expr 
%type 		<block> program stmts block 
%type 		<stmt> stmt var_decl var_decl_deduce func_decl conditional_if return while class_decl array_add_element /*print_stmt*/
%type 		<token> comparison debug_expr


/* Operator precedence for mathematical operators */
%left 		TPLUS TMINUS
%left 		TMUL TDIV
%left 		TAND TNOT

%start program
%debug 
%verbose 
%locations /* track locations: @n of component N; @$ of entire range */

%%

program 	: /* blank */ { programBlock = new harambe::Block(); }
		| stmts { programBlock = $1; }
		;

stmts 		: stmt { $$ = new harambe::Block(); $$->statements.push_back($<stmt>1); }
		| stmts stmt { $1->statements.push_back($<stmt>2); }
		;

stmt 		: var_decl
		| var_decl_deduce
		| func_decl
		| class_decl
		| conditional_if 
		| return
		| while
		| array_add_element
		| expr { $$ = new harambe::ExpressionStatement($1); }
		;

block 		: TBLOCKSTART stmts TBLOCKEND { $$ = $2; }
		| TBLOCKSTART TBLOCKEND { $$ = new harambe::Block(); }
		;
/*debug dont work*/
debug_expr	: DEBUGSTART  stmt DEBUGEND  { $$ = displayln($1); }
		| DEBUGSTART DEBUGEND { $$ = new harambe::PrintDebug(); }
		;

conditional_if 	: TIF TLPAREN expr TRPAREN block TELSE block {$$ = new harambe::Conditional($3,$5,$7);}
		| TIF TLPAREN expr TRPAREN block {$$ = new harambe::Conditional($3,$5);}
		; 

while 		: TWHILE TLPAREN expr TRPAREN block TELSE block {$$ = new harambe::WhileLoop($3,$5,$7);}
		| TWHILE TLPAREN expr TRPAREN block {$$ = new harambe::WhileLoop($3,$5);}
		; 

var_decl 	: ident ident { $$ = new harambe::VariableDeclaration($1, $2, @$); }
		| ident ident TEQUAL expr { $$ = new harambe::VariableDeclaration($1, $2, $4, @$); }
		;

var_decl_deduce	: TVAR ident TEQUAL expr { $$ = new harambe::VariableDeclarationDeduce($2, $4, @$); }
		;

func_decl 	: TDEF ident TLPAREN func_decl_args TRPAREN TRETURN ident block { $$ = new harambe::FunctionDeclaration($7, $2, $4, $8, @$); }
		| TDEF ident TLPAREN func_decl_args TRPAREN block { $$ = new harambe::FunctionDeclaration($2, $4, $6, @$); }
		;

func_decl_args 	: /*blank*/  { $$ = new harambe::VariableList(); }
		| var_decl { $$ = new harambe::VariableList(); $$->push_back($<var_decl>1); }
		| func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
		;

class_decl	: TDEF ident block {$$ = new harambe::ClassDeclaration($2, $3); }
		;

ident 		: TIDENTIFIER { $$ = new harambe::Identifier(*$1, @1); delete $1; }
		| TIDENTIFIER TDOT TIDENTIFIER { $$ = new harambe::Identifier(*$1,*$3, @$); delete $1; delete $3;}
		;

literals 	: TINTEGER { $$ = new harambe::Integer(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new harambe::Double(atof($1->c_str())); delete $1; }
		| TSTR { $$ = new harambe::String(*$1); delete $1; }
		| TBOOL { $$ = new harambe::Boolean(*$1); delete $1; }
		;


return 		: TRETURN expr { $$ = new harambe::Return(@$, $2); }
		| TRETURN_SIMPLE { $$ = new harambe::Return(@$); }
		;

expr 		: ident TEQUAL expr { $$ = new harambe::Assignment($<ident>1, $3, @$); }
		| ident TLPAREN call_args TRPAREN { $$ = new harambe::MethodCall($1, $3, @$);  }
		| ident { $<ident>$ = $1; }
		| literals
		| boolean_expr 
		| binop_expr
		| unaryop_expr
		| TLPAREN expr TRPAREN { $$ = $2; }
		| range_expr
		| array_expr
		| array_access
		;
/* have to write it explecity to have the right operator precedence */
binop_expr 	: expr TAND expr { $$ = new harambe::BinaryOp($1, $2, $3, @$); }
		| expr TOR expr { $$ = new harambe::BinaryOp($1, $2, $3, @$); }
		| expr TPLUS expr { $$ = new harambe::BinaryOp($1, $2, $3, @$); }
		| expr TMINUS expr { $$ = new harambe::BinaryOp($1, $2, $3, @$); }
		| expr TMUL expr { $$ = new harambe::BinaryOp($1, $2, $3, @$); }
		| expr TDIV expr { $$ = new harambe::BinaryOp($1, $2, $3, @$); }
		;

unaryop_expr 	: TNOT expr { $$ = new harambe::UnaryOperator($1, $2); }
		;

boolean_expr 	: expr comparison expr { $$ = new harambe::CompOperator($1, $2, $3); }
		;

call_args 	: /*blank*/  { $$ = new harambe::ExpressionList(); }
		| expr { $$ = new harambe::ExpressionList(); $$->push_back($1); }
		| call_args TCOMMA expr  { $1->push_back($3); }
		;
 
comparison 	: TCEQ | TCNE | TCLO | TCLE | TCGR | TCGE
		;
          
array_elemets_expr: /* blank */ {$$ = new harambe::ExpressionList(); }
		| expr {$$ = new harambe::ExpressionList(); $$->push_back($1);}
		| array_elemets_expr TCOMMA expr {$$->push_back($3); }
		; 
                 
array_expr 	: TLBRACKET array_elemets_expr TRBRACKET {$$ = new harambe::Array($2, @$);}
		;
          
array_add_element: ident TLTLT expr { $$ = new harambe::ArrayAddElement($1, $3, @$); }
		;
                
array_access	: ident TLBRACKET TINTEGER TRBRACKET { $$ = new harambe::ArrayAccess($1,atol($3->c_str()), @$); delete $3;}
		| array_access TLBRACKET TINTEGER TRBRACKET { $$ = new harambe::ArrayAccess($1,atol($3->c_str()), @$); delete $3;}
		;	

range_expr 	: TLBRACKET expr TRANGE expr TRBRACKET {$$ = new harambe::Range($2, $4, @$);}
		;

%%
