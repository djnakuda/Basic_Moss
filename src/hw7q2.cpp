#include <iostream>
#include <fstream>
#include "MossV1.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3){
		cout << "Need More Arguments\n";
		return 0;
	}

	ifstream inputFile1(argv[1]);
	ifstream inputFile2(argv[2]);

	Moss myMoss(inputFile1,inputFile2);

	if(myMoss.checkIfCheating())
	{
		cout << "cheating\n";
		myMoss.printMappingFrom1to2();
	}
	else
	{
		cout << "not cheating\n";
	}
	
	return 1;
}
