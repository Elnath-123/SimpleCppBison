/*
* @name bison.yy
* @description A Simple Tools of Expression Analysis
* @date 03/26/2020 
* @author Lrq
*/

%language "C++"
%defines
%locations
%skeleton "lalr1.cc"

%code{
	#include <iostream>
	#include <unistd.h>
	Ast* ast = new Ast();
}

%code requires{
	#include "ast.h"
	#include "visitor.h"
}
%union{
	AstNode* a;
	double d;
}

%parse-param {AstNode** root }

/* declearation */
%token EOL
%token <d> NUMBER
%token ADD SUB MUL DIV OP CP
%type <a> exp factor term

%{
	extern int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc);
%}
%%
	calclist:
	| calclist exp EOL{ printf("Recognized!\n"); *root = $2;}
	| calclist EOL { printf("> "); }
	;

	exp: factor {$$ = $1;}
	| exp ADD factor { $$ = new Plus($1, $3); }
	| exp SUB factor { $$ = new Sub($1, $3); }	
	;

	factor: term {$$ = $1;}
	| factor MUL term { $$ = new Mul($1, $3);} 
	| factor DIV term { $$ = new Div($1, $3);}
	;

	term: NUMBER  { $$ = new Num($1); }
	| OP exp CP { $$ = $2; }
	;
%%

void usage();

int main(int argc, char** argv)
{	
    /* Get command from shell */
	int eval = 0;
	int infix = 0;
	char opt;
	while((opt = getopt(argc, argv, "hei")) != -1){
		switch (opt){
			case 'h':
				usage();
			break;
			case 'e':
				eval = 1;
			break;
			case 'i':
				infix = 1;
			break;
		default:
				usage();
		}
	}
	/* No argument */
	if(eval == 0 && infix == 0) usage();
	
	/* Parse */
	AstNode *root;
	yy::parser parser(&root);
	parser.parse();
	if(root == NULL){
		std::cerr << "error!!" << std::endl;
		exit(0);
	}
	
	/* Analyse Expression */
	if(eval == 1){
		EvalVisitor* ev = new EvalVisitor();
		double v = root->accept(ev);
		std::cout << "By Visitor Pattern: Value=" << v << std::endl;
	}
	if(infix == 1){
		InfixVisitor* iv = new InfixVisitor();
		std::cout << "Infix Expression::";
		root->accept(iv);
		std::cout << std::endl;
	}

	/* Not Visitor pattern (reserved) */
	//std::cout << "By Default: Value=" << root->eval() << std::endl;
	
	return 0;
}

void usage(){
	printf("Usage: target [-hei]\n");
	printf("   -h   print this message\n");
	printf("   -e   print evaluation of target expression\n");
	printf("   -v   print infix of target expression\n");
	exit(1);
}

namespace yy{
	void
	parser::error(location const &loc, const std::string &s){
			std::cerr << "error at " << loc << ": " << s << std::endl;
	}
}
