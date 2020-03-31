/*
 * @name driver.cpp
 * @description A driver for parse program
 * @date 03/31/2020
 * @author Lrq
 */

#include <iostream>
#include <unistd.h>
#include "bison.tab.hxx"

void usage();

int main(int argc, char** argv)
{	
    /* Get command from shell */
	int eval = 0;
	int postfix = 0;
	char opt;

	while((opt = getopt(argc, argv, "hep")) != -1){
		switch (opt){
			case 'h':
				usage();
			break;
			case 'e':
				eval = 1;
			break;
			case 'p':
				postfix = 1;
			break;
		default:
				usage();
		}
	}

	/* No argument */
	if(eval == 0 && postfix == 0) usage();
	
	/* Parse */
	Expression *root;
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
	if(postfix == 1){
		PostfixVisitor* pv = new PostfixVisitor();
		std::cout << "Postfix Expression:";
		root->accept(pv);
		std::cout << std::endl;	
	}

	return 0;
}

void usage(){
	printf("Usage: target [-hei]\n");
	printf("   -h   print this message\n");
	printf("   -e   print evaluation of target expression\n");
	printf("   -p   print postfix of target expression\n");
	exit(1);
}

