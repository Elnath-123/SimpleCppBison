#include "visitor.h"
#include "ast.h"	
#define RET_FROM_BINOP 114514.1919810
double EvalVisitor::visit ( Expression* n ){
	double v;
	if (n->type == "Plus")
		v = n->left->accept(this) + n->right->accept(this);
	else if (n->type == "Sub")
		v = n->left->accept(this) - n->right->accept(this);
	else if (n->type == "Mul")
		v = n->left->accept(this) * n->right->accept(this);
	else if (n->type == "Div")
		v = n->left->accept(this) / n->right->accept(this);
	return v;
}
double EvalVisitor::visit( Num* n){
	return n->val;
}
double PostfixVisitor::visit( Expression* n ){
	double vLeft  = n->left->accept(this);
	if(vLeft != RET_FROM_BINOP) std::cout << vLeft << ' ';
	double vRight = n->right->accept(this);	
	if(vRight != RET_FROM_BINOP) std::cout << vRight << ' ';
	if (n->type == "Plus")
		std::cout << '+' << ' ';		
	else if (n->type == "Sub")
		std::cout << '-' << ' ';
	else if (n->type == "Mul")
		std::cout << '*' << ' ';
	else if (n->type == "Div")
		std::cout << '/' << ' ';
	return RET_FROM_BINOP;
}

double PostfixVisitor::visit( Num* n){
	return n->val;
}

