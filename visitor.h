#ifndef _VISITOR_H
#define _VISITOR_H
class AstNode;
class BinOp;
class Expression;
class Num;

class Visitor{
public:
	virtual double visit ( Expression* n ) = 0;
	virtual double visit ( Num* n) = 0;
};

class EvalVisitor : public Visitor{	
public:
	virtual double visit ( Expression* n );
	virtual double visit ( Num* n );
};

class PostfixVisitor : public Visitor{
public:
	virtual double visit ( Expression* n );
	virtual double visit ( Num* n );
};
#endif
