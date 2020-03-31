#ifndef _AST_H
#define _AST_H
#include <iostream>
#include "visitor.h"
class AstNode{
public:
	AstNode(){ }
	virtual double eval() = 0;
	virtual double accept( Visitor* v ) = 0;
};

class BinOp : public AstNode{
public:
	std::string optype;
	AstNode* left;
	AstNode* right;
	BinOp( std::string optype, AstNode* left, AstNode* right ) : 
				optype(optype), left(left), right(right){ }
	
};

class Plus : public BinOp{
public:
	double eval() override;
	double accept( Visitor* v){ return v->visit(this); }
	Plus( AstNode* left, AstNode* right ) :
		BinOp(std::string("Plus"), left, right) { }
};


class Sub : public BinOp{
public:
	double eval() override;
	double accept( Visitor* v){ return v->visit(this); }
	Sub( AstNode* left, AstNode* right ) :
		BinOp(std::string("Sub"), left, right) { }
};


class Mul : public BinOp{
public:
	double eval() override;
	double accept( Visitor* v ){ return v->visit(this); }
	Mul( AstNode* left, AstNode* right ) :
		BinOp(std::string("Mul"), left, right) { }
};


class Div : public BinOp{
public:
	double eval() override;
	double accept( Visitor* v){ return v->visit(this); }
	Div( AstNode* left, AstNode* right ) :
		BinOp(std::string("Div"), left, right) { }
};

class Num : public AstNode{
public:		
	double val;
	double eval() override { return val; }
	double accept( Visitor* v){ return v->visit(this); }
	Num( double val ): val(val){}	
};

class Ast{
public:
	//AstNode* root;
	Ast() {}
	void genInfixExp();
	void treeFree();
};
#endif
