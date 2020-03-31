#ifndef _VISITOR_H
#define _VISITOR_H
class AstNode;
class BinOp;
class Plus;
class Sub;
class Mul;
class Div;
class Num;

class Visitor{
public:
	virtual double visit ( Plus* n ) = 0;
	virtual double visit ( Sub* n  ) = 0;
	virtual double visit ( Mul* n  ) = 0;
	virtual double visit ( Div* n  ) = 0;
	virtual double visit ( Num* n  ) = 0;
};

class EvalVisitor : public Visitor{	
public:
	virtual double visit ( Plus* n );
	virtual double visit ( Sub* n  );
	virtual double visit ( Mul* n  );
	virtual double visit ( Div* n  );
	virtual double visit ( Num* n  );
};

class InfixVisitor : public Visitor{
public:
	virtual double visit ( Plus* n );
	virtual double visit ( Sub* n  );
	virtual double visit ( Mul* n  );
	virtual double visit ( Div* n  );
	virtual double visit ( Num* n  );	
};
#endif
