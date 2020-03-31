%option noyywrap nodefault yylineno
%{
#include "bison.tab.hxx"
#include "ast.h"
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, \
		yy::parser::location_type *yylloc)

#define YY_USER_ACTION yylloc->columns (yyleng);
%}


EXP ([Ee][-+]?[0-9]+)
%%
%{
	yylloc->step();
%}
"+" {return yy::parser::token::ADD;}
"-" {return yy::parser::token::SUB;}
"*" {return yy::parser::token::MUL;}
"/" {return yy::parser::token::DIV;}
"(" {return yy::parser::token::OP;}
")" {return yy::parser::token::CP;}


[0-9]+"."[0-9]+ |
[0-9]+ { yylval->d = atof(yytext); return yy::parser::token::NUMBER;}

\n { yylloc->lines(1); return yy::parser::token::EOL;}
[ \t] { yylloc->step(); }
. {printf("Invalid character %c\n", *yytext);}

%%
