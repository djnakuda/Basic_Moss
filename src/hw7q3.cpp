#include <iostream>
#include <fstream>
#include "MossV3.h"

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

	if(myMoss.Check())
	{
		cout << "cheating\n";
		myMoss.printMappingFrom1to2();
	}
	else
	{
		cout << "not cheating\n";
		//myMoss.printMappingFrom1to2();
	}
	
	return 1;
}
