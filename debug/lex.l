%option noyywrap nodefault yylineno
%{
#include "bison.tab.hh"
#include "ast.h"
typedef yy::parser::semantic_type type;
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, \
		yy::parser::location_type *yylloc)

%}


EXP ([Ee][-+]?[0-9]+)
%%
"+" {return yy::parser::token::ADD;}
"-" {return yy::parser::token::SUB;}
"*" {return yy::parser::token::MUL;}
"/" {return yy::parser::token::DIV;}
"(" {return yy::parser::token::OP;}
")" {return yy::parser::token::CP;}


[0-9]+"."[0-9]+ |
[0-9]+ { yylval->d = atof(yytext); return yy::parser::token::NUMBER;}

\n {return yy::parser::token::EOL;}
[ \t] { }
. {printf("Invalid character %c\n", *yytext);}

%%
