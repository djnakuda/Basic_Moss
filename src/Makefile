all: hw7q2 hw7q3

hw7q2: hw7q2.cpp avlbst.h MossV1.o
	g++ -g -Wall -std=c++11 hw7q2.cpp BooleanExpression.o ArithmeticExpression.o Command.o RecursiveParser.o Variable.o MossV1.o -o hw7q2

hw7q3: hw7q3.cpp avlbst.h MossV3.o
	g++ -g -Wall -std=c++11 hw7q3.cpp BooleanExpression.o ArithmeticExpression.o Command.o RecursiveParser.o Variable.o MossV3.o -o hw7q3

MossV1.o: MossV1.cpp MossV1.h bst.h avlbst.h
	g++ -g -Wall -std=c++11 -c MossV1.cpp -o MossV1.o

MossV3.o: MossV3.cpp MossV3.h bst.h avlbst.h
	g++ -g -Wall -std=c++11 -c MossV3.cpp -o MossV3.o

clean:
	rm MossV1.o
	rm MossV3.o
	rm hw7q2
	rm hw7q3