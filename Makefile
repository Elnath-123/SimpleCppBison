target: lex.l bison.yxx ast.h visitor.h visitor.cpp
	bison -d bison.yxx
	flex lex.l
	g++ -o $@ bison.tab.cxx lex.yy.c ast.cpp visitor.cpp driver.cpp

.PYHONY: clean
clean:
	rm bison.tab.cxx \
	bison.tab.hxx \
	lex.yy.c \
	location.hh \
	position.hh \
	stack.hh \
	target

