#include "MossV1.h"

using namespace std;

Moss::Moss(std::ifstream& inputFile1, std::ifstream& inputFile2){

	file1 = new RecursiveParser(inputFile1);
	file2 = new RecursiveParser(inputFile2);
	CommadVectorOne = file1->GetCommands();
	CommadVectorTwo = file2->GetCommands();

	for(unsigned int i = 0;i < CommadVectorOne.size();i++)
	{
		LineToIndex1.insert(pair<int,int>(CommadVectorOne[i]->GetLineNumber(),i));
	}

	for(unsigned int i = 0;i < CommadVectorTwo.size();i++)
	{
		LineToIndex2.insert(pair<int,int>(CommadVectorTwo[i]->GetLineNumber(),i));
	}
}

Moss::~Moss()
{
	delete file1;
	delete file2;
}

bool Moss::checkIfCheating()
{
	if(CommadVectorOne.size() != CommadVectorTwo.size()) // If different size command vectors just return
	{
		return false;
	}
	for(unsigned int i = 0; i < CommadVectorTwo.size();i++)
	{
		if(!checkCommands(CommadVectorOne[i],CommadVectorTwo[i])) return false;
	}

	return true;
}

/*
Returns true if the same Arithmetic Expression
*/
bool Moss::checkIfArithAreSame(ArithmeticExpression* ae1,ArithmeticExpression* ae2)
{
	if(ae1->GetClassId() == ae2->GetClassId())
	{
		if(ae1->GetClassId() == "ConstantArithmeticExpression")
		{
			if(((ConstantArithmeticExpression*)(ae1))->GetConstantValue() == ((ConstantArithmeticExpression*)(ae2))->GetConstantValue()) return true;
			else return false;
		}
		else if(ae1->GetClassId() == "IntVariableArithmeticExpression")
		{
			const string s1 =((IntVariableArithmeticExpression*)(ae1))->GetIntVariable()->GetName();
			const string s2 =((IntVariableArithmeticExpression*)(ae2))->GetIntVariable()->GetName();
			AVLTree<string,string>::iterator it1 = VariableHolderOnetoTwo.find(s1);
			AVLTree<string,string>::iterator it2 = VariableHolderTwotoOne.find(s2);

			if(it1 == VariableHolderOnetoTwo.end())//No Mapping from s1 
			{
				if(it2 == VariableHolderTwotoOne.end())// mapping from s1 and s2 doesn't exist
				{
					VariableHolderOnetoTwo.insert(pair<string,string>(s1,s2)); //Just add to maps and consider that their still cheating
					VariableHolderTwotoOne.insert(pair<string,string>(s2,s1));
					return true;
				}
				else//mapping from s1 doesn't exist but does exist from s2
				{
					return false;
				}
			}
			else//mapping from s1 exists
			{
				if(it2 == VariableHolderTwotoOne.end()) //No mapping from s2 but mapping from s1
				{
					return false;
				}
				else //Mapping from s2 and s1
				{
					if(it2->second == s1) //it2 maps correctly to s1
					{
						if(it1->second == s2) //it1 maps correctly maps to s2
						{
							return true;
						}

						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}

			}
		}
		else if(ae1->GetClassId() == "ArrayVariableArithmeticExpression")
		{
			const string s1 =((ArrayVariableArithmeticExpression*)(ae1))->GetArrayVariable()->GetName();
			const string s2 =((ArrayVariableArithmeticExpression*)(ae2))->GetArrayVariable()->GetName();
			ArithmeticExpression* index1 = ((ArrayVariableArithmeticExpression*)(ae1))->GetArrayIndex();
			ArithmeticExpression* index2 = ((ArrayVariableArithmeticExpression*)(ae2))->GetArrayIndex();
			AVLTree<string,string>::iterator it1 = ArrayHolderOnetoTwo.find(s1);
			AVLTree<string,string>::iterator it2 = ArrayHolderTwotoOne.find(s2);

			if(!checkIfArithAreSame(index1,index2)) return false;

			if(it1 == ArrayHolderOnetoTwo.end())//No Mapping from s1 
			{
				if(it2 == ArrayHolderTwotoOne.end())// mapping from s1 and s2 doesn't exist
				{
					ArrayHolderOnetoTwo.insert(pair<string,string>(s1,s2)); //Just add to maps and consider that their still cheating
					ArrayHolderTwotoOne.insert(pair<string,string>(s2,s1));
					return true;
				}
				else//mapping from s1 doesn't exist but does exist from s2
				{
					return false;
				}
			}
			else//mapping from s1 exists
			{
				if(it2 == ArrayHolderTwotoOne.end()) //No mapping from s2 but mapping from s1
				{
					return false;
				}
				else //Mapping from s2 and s1
				{
					if(it2->second == s1) //it2 maps correctly to s1
					{
						if(it1->second == s2) //it1 maps correctly maps to s2
						{
							return true;
						}

						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}

			}
		}
		else if(ae1->GetClassId() == "AdditionExpression" || ae1->GetClassId() == "SubtractionExpression" || ae1->GetClassId() == "MultiplicationExpression" || ae1->GetClassId() == "DivisionExpression")
		{
			ArithmeticExpression* ae1Lhs = ((BinaryArithmeticExpression*)(ae1))->GetLhs();
			ArithmeticExpression* ae1Rhs = ((BinaryArithmeticExpression*)(ae1))->GetRhs();
			ArithmeticExpression* ae2Lhs = ((BinaryArithmeticExpression*)(ae2))->GetLhs();
			ArithmeticExpression* ae2Rhs = ((BinaryArithmeticExpression*)(ae2))->GetRhs();

			if((checkIfArithAreSame(ae1Lhs,ae2Lhs) && checkIfArithAreSame(ae1Rhs,ae2Rhs))) return true;
			else return false;
		}
		else return false;
	}
	return false;
}

void Moss::printMappingFrom1to2()
{
	AVLTree<string,string>::iterator i = VariableHolderOnetoTwo.begin();
	AVLTree<string,string>::iterator j = ArrayHolderOnetoTwo.begin();
	while((i != VariableHolderOnetoTwo.end()) || (j != ArrayHolderOnetoTwo.end()))
	{
		if(i == VariableHolderOnetoTwo.end())
		{
			cout << j->first << " " << j->second << endl;
			++j;
		}
		else if( j == ArrayHolderOnetoTwo.end())
		{
			cout << i->first << " " << i->second << endl;
			++i;
		}
		else {
			if((i->first < j->first))
			{
				cout << i->first << " " << i->second << endl;
				++i;
			}
			else
			{
				cout << j->first << " " << j->second << endl;
				++j;
			}
		}
	}
}

bool Moss::checkCommands(Command* c1,Command* c2)
{
	if(c1->GetClassId() == c2->GetClassId())
	{
			if(c2->GetClassId() == "PrintCommand")
			{
				 if(!checkPrintCommands((PrintCommand*)c1,(PrintCommand*)c2)) return false;
			}
			else if(c2->GetClassId() == "LetCommand")
			{
				if(!checkLetCommands((LetCommand*)c1,(LetCommand*)c2)) return false;
			}
			else if(c2->GetClassId() == "GoToCommand")
			{
				if(!checkGoToCommands((GoToCommand*)c1,(GoToCommand*)c2)) return false;
			}
			else if(c2->GetClassId() == "IfThenCommand")
			{
				if(!checkIfCommands((IfThenCommand*)c1,(IfThenCommand*)c2)) return false;
			}
			else if(c2->GetClassId() == "GoSubCommand")
			{
				if(!checkGoSubCommands((GoSubCommand*)c1,(GoSubCommand*)c2)) return false;
			}
			else //END COMMAND OR RETURN, Should Check Nohting
			{

			}
	}
	else
	{
		return false;
	}
	return true;
}

/*
Returns True if the Arithmetic Equations are Equal to each other
*/
bool Moss::checkPrintCommands(PrintCommand* p1, PrintCommand* p2)
{
	return checkIfArithAreSame(p1->GetArithmeticExpression(),p2->GetArithmeticExpression());
}

bool Moss::checkLetCommands(LetCommand* l1, LetCommand* l2)
{
	VariableArithmeticExpression* Var1 = l1->GetVariableExpression();
	VariableArithmeticExpression* Var2 = l2->GetVariableExpression();

	ArithmeticExpression* AE1 = l1->GetArithmeticExpression();
	ArithmeticExpression* AE2 = l2->GetArithmeticExpression();

	bool VarSame = checkIfArithAreSame(Var1,Var2);
	bool AESame = checkIfArithAreSame(AE1,AE2);

	if(VarSame && AESame) return true;
	return false;
}

bool Moss::checkJumpCommads(int lineJump1,int lineJump2)
{
	int index1 = -1, index2 = -1;

	AVLTree<int,int>::iterator it1 = LineToIndex1.find(lineJump1);
 	if(it1 != LineToIndex1.end())index1 = it1->second;

	it1 = LineToIndex2.find(lineJump2);
	if(it1 != LineToIndex2.end())index2 = it1->second;

	if(index1 != index2) return false;
	return true;
}

bool Moss::checkGoToCommands(GoToCommand* gt1, GoToCommand* gt2)
{
	int lineJump1 = gt1->GetDstLine();
	int lineJump2 = gt2->GetDstLine();

	return checkJumpCommads(lineJump1,lineJump2);
}

bool Moss::checkGoSubCommands(GoSubCommand* gs1, GoSubCommand* gs2)
{
	int lineJump1 = gs1->GetDstLine();
	int lineJump2 = gs2->GetDstLine();

	return checkJumpCommads(lineJump1,lineJump2);
}

bool Moss::checkIfCommands(IfThenCommand* if1,IfThenCommand* if2)
{
	BinaryBooleanExpression* be1 = (BinaryBooleanExpression*)if1->GetBooleanExpression();
	BinaryBooleanExpression* be2 = (BinaryBooleanExpression*)if2->GetBooleanExpression();

	if(!checkifBooleanExpressionIsSame(be1,be2)) return false;

	//Make Changes
	int lineJump1 = if1->GetDstLine();
	int lineJump2 = if2->GetDstLine();

	return checkJumpCommads(lineJump1,lineJump2);
}

bool Moss::checkifBooleanExpressionIsSame(BinaryBooleanExpression* be1,BinaryBooleanExpression* be2)
{
	if(be1->GetClassId() != be2->GetClassId())return false;

	ArithmeticExpression* lhs1 = be1->GetLhs();
	ArithmeticExpression* lhs2 = be2->GetLhs();
	ArithmeticExpression* rhs1 = be1->GetRhs();
	ArithmeticExpression* rhs2 = be2->GetRhs();

	if(!checkIfArithAreSame(lhs1,lhs2) || !checkIfArithAreSame(rhs1,rhs2)) return false;

	return true;
}
