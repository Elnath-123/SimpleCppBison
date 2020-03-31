# Cpp Flex and Bison Document
&emsp;本项目使用c++语言编写的bison，与c语言编写的flex构建了一个简单的表达式分析系统。
## 0.1 阅读前备知识
1. flex and bison for C language 的基础知识
2. c++语法的基础知识，包括封装，继承，多态，虚函数，命名空间，以及输入输出流的使用等。
3. c语言的基础知识，包括指针，宏定义等。
请确保你已经有以上的知识后再来阅读。

## 0.2 主要内容
&emsp;本文档主要介绍c++bison的写法，如何兼容c语言的flex，以及如何使用观察者模式来对抽象语法树（AST）进行分析。

## 1.1 C++ bison
&emsp;每当你创建c++语法分析器时，bison会创建四个类的头文件：location.hh，position.hh用来定义位置结构，stack.hh定义内部语法分析器堆栈，以及*.tab.hh文件来定义语法分析器自身。与c语言不同，bison将在yy命名空间中创建语法分析器，其类名为parser，其中有一个方法叫做parse，你可以在实例化该类后调用此函数。此外，token也定义在parser中。

## 1.2 c++兼容的c flex写法
1. 使用%lex-param声明，为lex传入参数。（可选） 
2. 由于parser在parse的过程中需要使用到yylex函数，但由于两者并不是同一个语言所编写，因此需要定义与生成的bison文件中yylex所匹配的函数。即定义宏YY_DELC
```c
/* No parameter */
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc);

/* Have parameters */
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc, /*your parameter */);
```
3. 处理位置信息，定义宏 YY_USER_ACTION，其会在语义动作执行之前进行调用，具体实现由用户自行定义。

## 1.3 C++ bison的写法
1. 在bison的Declaration中，首先需要进行声明：`%language "C++"`，说明此文件使用c++进行编写。
2. 引入代码，分为无条件形式引入（unqualified form）及条件形式引入(qualified form)
- 对于无条件形式引入，其将会在parser的头文件内容之后。形式为%code{'your code'}
- 有条件引入的条件分为requires, provides, top。
require: 在bison头文件中，以及在实现文件生成YYLTYPE， YYSTYPE之后插入代码
provides: 在bison头文件中，以及在实现文件生成YYLTYPE， YYSTYPE，以及token定义之前插入代码
top: 在bison实现文件的顶部插入代码
详见bison文档:https://www.gnu.org/software/bison/manual/html_node/_0025code-Summary.html
3. %parse-param声明，用来将parser中的参数传递给driver程序。
4. %location声明，用来把处理位置信息的代码加入语法分析器，这样yylloc才可以使用。
5. 由于生成的parser中，需要使用yylex函数，因此声明：
```c
extern int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc);
```

## 2.1 观察者模式(Visitor Pattern)
&emsp;观察者模式是设计模式中的一种，其本质是利用面向对象中的多态型 (polymorphic)将类间解耦合。在处理抽象语法树(AST)的过程中可以充分的体现其优势。
&emsp;观察者模式可以简单的理解成"主题-订阅"模式。其表示了多对多的关系，一个观察者可以订阅多个主题，一个主题也可以被多个观察者订阅。比如AST的节点就是一个主题，我们可以使用许多观察者来订阅AST主题，这些观察者所拥有的方法，就是来对AST节点进行操作。例如表达式求值，以及生成后缀表达式。
每一个主题拥有一个accept函数，用来接受Visitor的访问。每一个观察者都有一个visit方法，用来访问主题。即：
```c++
/* In a class of Subject file */
Returnval SubjectClassName::accept(Visitor v){return v->visit(this);}
/* In Visitor file */
Returnval VisitorClassName::visit(Subject* node){
    /* Define your own operation for node */
}

/* In main */
/* Defination of Subject */
SubjectA subject = new SubjectA();
VisitorA va = new VisitorA();
VisitorB vb = new VisitorB();
...

/* Accept the visitor */
subjectA->accept(va); 
subjectA->accept(vb);
...
```
&emsp;我们可以发现，虽然SubjectA中只有一个accept方法，但其利用了多态性，对于不同Visitor(这里为VisitorA和VisitorB)，其完成了不同的功能。因此，如果想要添加对主题的访问功能，使用观察者模式，只需要定义一个新的Visitor，当作参数传给主题，即可完成这个功能，而不需要更改任何的主题内容。这样做，更利益扩展和维护。

## 2.2 观察者模式在表达式分析中的体现
1. 定义抽象语法树节点。
AstNode为父类，Expression表达式类继承于AstNode，Binop二元运算符继承于Expression，Num浮点型常量继承于Expression。
```c++
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
	virtual double accept (Visitor* v) = 0;
};

class Expression : public AstNode{
public:
	std::string type;
	Expression* left;
	Expression* right;
	Expression () { }
	Expression (std::string type): type(type) { }
	Expression (std::string type, Expression* left, Expression* right) :
                type (type), left (left), right (right) { }
};

class BinOp : public Expression{
public:
	double accept (Visitor* v) {return v->visit(this);}
	BinOp (std::string type, Expression* left, Expression* right ) : 
				Expression (type, left, right) { }
	
};

class Num : public Expression{
public:		
	double val;
	double accept (Visitor* v) { return v->visit(this); }
	Num(std::string type, double val): 
        Expression (type), val (val){}	
};

#endif

```
2. 定义观察者类
Visitor为父类接口，EvalVisitor和PostfixVisitor继承于Visitor并实现了父类的纯虚函数。
```c++
#ifndef _VISITOR_H
#define _VISITOR_H
class AstNode;
class BinOp;
class Expression;
class Num;

class Visitor{
public:
	virtual double visit (Expression* n) = 0;
	virtual double visit (Num* n) = 0;
};

class EvalVisitor : public Visitor{	
public:
	virtual double visit (Expression* n);
	virtual double visit (Num* n);
};

class PostfixVisitor : public Visitor{
public:
	virtual double visit (Expression* n);
	virtual double visit (Num* n);
};
#endif
```
在Visitor.cpp中，实现了EvalVisitor和PostfixVisitor类中的visit函数。
在主函数中，我们可以使用观察者模式对表达式进行分析：
```c++
/* In driver.cpp */
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
```
## 3.1 使用方法
- 安装flex和bison
`sudo apt install flex bison`
- 进入目录并编译
`cd $YOUR_PATH/cppbisonsample && make`
- 运行程序
**命令行参数：**
-e: 分析表达式并求值
-p: 输出后缀表达式
-h: 输出帮助信息
`./target -[hep]`

## 3.2 实验环境
linux ubuntu-18.04（本机使用wsl）, g++-7.5.0, flex-2.6.4, bison-3.0.4