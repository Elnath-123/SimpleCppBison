/*
* @name ast.h
* @description Hierachy of AST
* @date 03/31/2020
* @author Lrq 
*                        |---------|
*                        | AstNode |
*                        |---------|
*                             |
*                             |
*                      |--------------|
*                      |  Expression  |
*                      |--------------|
*                          |      |
*                         |        |
*                        |          |
*                    |-------|    |-------|
*                    | BinOp |    |  Num  |
*                    |-------|    |-------|
*/
#ifndef _AST_H
#define _AST_H
#include <iostream>
#include "visitor.h"

class AstNode{
public:
	AstNode(){ }
	virtual double accept( Visitor* v ) = 0;
};

class Expression : public AstNode{
public:
	std::string type;
	Expression* left;
	Expression* right;
	Expression(){ }
	Expression(std::string type): type(type)	{ }
	Expression(std::string type, Expression* left, Expression* right) : type(type), left(left), right(right) { }
};

class BinOp : public Expression{
public:
	double accept( Visitor* v) {return v->visit(this);}
	BinOp( std::string type, Expression* left, Expression* right ) : 
				Expression(type, left, right){ }
	
};

class Num : public Expression{
public:		
	double val;
	double accept( Visitor* v){ return v->visit(this); }
	Num( std::string type, double val ): Expression(type), val(val){}	
};

#endif
