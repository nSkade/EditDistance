#include <iostream>
#include <string>
#include <vector>

#include "editdistance.hpp"
#include "stringConstructor.hpp"

#include "terminal_ui.hpp"

int main(int argc, char* argv[])
{
	if(argc < 3) return -1;

	std::string initWord(argv[1]);
	std::string goalWord(argv[2]);

	std::vector<std::vector<int>> editDistanceMatrix(initWord.size()+1,std::vector<int>(goalWord.size()));

	// fill matrix
	createMatrix(&editDistanceMatrix, initWord.size(), goalWord.size());
	//printf("\nfilled Matrix:\n\n");
	//printEditDistance(editDistanceMatrix, initWord, goalWord);

	// calculate edit distance
	fillEditDistance(editDistanceMatrix, initWord, goalWord, true);

	// print calculated matrix
	printf("\ncalculated Matrix:\n\n");
	printEditDistance(editDistanceMatrix, initWord, goalWord);

	printf("\nMinimal Edit Distance: %d\n", getMinEditDistance(editDistanceMatrix));

	//
	// print backtrace results
	//
	
	printf("\ndebug Operations:\n%s\n", backtraceTwd(editDistanceMatrix.size()-1, editDistanceMatrix.at(0).size()-1, editDistanceMatrix, initWord, goalWord, true).c_str());

	std::string operations = backtraceTwd(editDistanceMatrix.size()-1, editDistanceMatrix.at(0).size()-1, editDistanceMatrix, initWord, goalWord, false);

	printOperations(operations);
	// detectKill(&operations);
	// printOperations(operations);

	std::string iterations("");
	std::string transition("");
	
	printf("\nprocessed string: %s\n", createNewStr(initWord, goalWord, operations, &iterations).c_str());
	printf("\niterations new string:\n%s\n", iterations.c_str());
	
	changeExistingStr(&initWord, goalWord, operations, &transition);

	printf("\niterations existing string:\n%s\n", transition.c_str());

	printf("\nword has been changed to: %s\n", initWord.c_str());

	return 0;
}
