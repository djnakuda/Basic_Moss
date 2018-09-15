#ifndef MOSSV1_H
#define MOSSV1_H

#include "BooleanExpression.h"
#include "ArithmeticExpression.h"
#include "Token.h"
#include "Command.h"
#include "RecursiveParser.h"
#include "Variable.h"
#include "avlbst.h"

class Moss{
public:
	Moss(std::ifstream& inputFile1, std::ifstream& inputFile2);
	~Moss();
	bool checkIfCheating();
	void printMappingFrom1to2();
private:
	bool checkIfArithAreSame(ArithmeticExpression* ae1,ArithmeticExpression* ae2);
	bool checkPrintCommands(PrintCommand* p1, PrintCommand* p2);
	bool checkLetCommands(LetCommand* l1, LetCommand* l2);
	bool checkGoToCommands(GoToCommand* gt1, GoToCommand* gt2);
	bool checkGoSubCommands(GoSubCommand* gs1, GoSubCommand* gs2);
	bool checkIfCommands(IfThenCommand* if1,IfThenCommand* if2);
	bool checkifBooleanExpressionIsSame(BinaryBooleanExpression* be1,BinaryBooleanExpression* be2);
	bool checkCommands(Command* c1,Command* c2);
	bool checkJumpCommads(int lineJump1,int lineJump2);
private:
	RecursiveParser* file1;
	RecursiveParser* file2;
	std::vector<Command*> CommadVectorOne;
	std::vector<Command*> CommadVectorTwo;

	AVLTree<std::string,std::string> VariableHolderOnetoTwo;
	AVLTree<std::string,std::string> VariableHolderTwotoOne;
	AVLTree<std::string,std::string> ArrayHolderOnetoTwo;
	AVLTree<std::string,std::string> ArrayHolderTwotoOne;
	AVLTree<int,int> LineToIndex1;
	AVLTree<int,int> LineToIndex2;
	
};

#endif