target: lex.l bison.y ast.h
	bison -d -t bison.y
	flex -d lex.l
	g++ -o $@ bison.tab.cc lex.yy.c ast.cpp visitor.cpp

.PYHONY: clean
clean:
	rm bison.tab.cc \
	bison.tab.hh \
	lex.yy.c \
	location.hh \
	position.hh \
	stack.hh \
	target

