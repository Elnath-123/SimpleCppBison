#include "visitor.h"
#include "ast.h"
double EvalVisitor::visit ( Plus* n ){
	return n->left->accept(this) + n->right->accept(this);
}
double EvalVisitor::visit ( Sub* n ){
	return n->left->accept(this) - n->right->accept(this);
}
double EvalVisitor::visit ( Mul* n ){
	return n->left->accept(this) * n->right->accept(this);
}
double EvalVisitor::visit ( Div* n ){
	return n->left->accept(this) / n->right->accept(this);
}
double EvalVisitor::visit ( Num* n ){
	return n->val;
}

double InfixVisitor::visit ( Plus* n ){
	n->left->accept(this);
	std::cout << '+';
	n->right->accept(this);
}
double InfixVisitor::visit ( Sub* n ){
	n->left->accept(this);
	std::cout << '-';
	n->right->accept(this);
}
double InfixVisitor::visit ( Mul* n ){
	n->left->accept(this);
	std::cout << '*';
	n->right->accept(this);
}
double InfixVisitor::visit ( Div* n ){
	n->left->accept(this);
	std::cout << '/';
	n->right->accept(this);
}
double InfixVisitor::visit ( Num* n ){
	std::cout << n->val;
}
