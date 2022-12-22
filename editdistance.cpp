#include "editdistance.hpp"
#include "elementOps.hpp"

#include <vector>
#include <string>
#include <algorithm>

//TODO
void createMatrix(std::vector<std::vector<int>>* matrix, int initSize, int goalSize)
{
	(*matrix) = std::vector<std::vector<int>>(initSize+1,std::vector<int>(goalSize+1,0));
	for(int i = 0; i < initSize+1; i++)
	{
		for(int j = 0; j < goalSize+1; j++)
		{
			(*matrix)[i][j] = 0;
			if (i==0)
				(*matrix)[i][j] = j;
			if (j==0)
				(*matrix)[i][j] = i;
		}
	}
}

// TODO Add comments cleanup
// TODO change *matrix to &matrix
void fillEditDistance(std::vector<std::vector<int>>* matrix, std::string init, std::string target, bool twiddle)
{
	int k = 0;
	for(int i = 0; i < (*matrix).size(); i++) {
		// we already have the result for the empty string so skip first line
		if(i == 0) continue;
		
		for(int j = 0; j < (*matrix)[i].size(); j++) {
			if(j == 0) {
				continue;
			}
			(*matrix)[i][j] = (*matrix)[i-1][j]+1; // del

			if((*matrix)[i][j-1] + 1 < (*matrix)[i][j]) {
				(*matrix)[i][j] = (*matrix)[i][j-1] + 1; //ins
			}
			
			if(init.at(i-1) == target.at(j-1)) k = 0;
			else k = 1;
			
			if((*matrix)[i-1][j-1] + k < (*matrix)[i][j]) {
				// k = 1 rep // k = 0 skp
				(*matrix)[i][j] = (*matrix)[i-1][j-1]+k;
			}
			
			// twiddle
			if (twiddle && i <= init.size() && j <= target.size() && i > 1 && j > 1) {
				if((*matrix)[i-2][j-2]+1 < (*matrix)[i][j]) {
					// remember that index 0 is the empty word, so our word starts at index 1
					if(init.at(i-2) == target.at(j-1) && init.at(i-1) == target.at(j-2)) {
						//TODO check for cost
						(*matrix)[i][j] = (*matrix)[i-2][j-2]+1;
					}
				}
			}
		}
	}
}

int getMinEditDistance(std::vector<std::vector<int>> matrix)
{
	int i = matrix.size();
	int j = matrix[i-1].size();
	
	return matrix[i-1][j-1];
}

std::string backtrace(int i, int j, std::vector<std::vector<int>> matrix, bool debug)
{
	if (i>0 && matrix[i-1][j] + 1 == matrix[i][j])
		return backtrace(i-1, j, matrix, debug) + (debug ? " del " : std::string(1, char(DELETE)));
	if (j>0 && matrix[i][j-1] + 1 == matrix[i][j])
		return backtrace(i, j-1, matrix, debug) + (debug ? " ins " : std::string(1, char(INSERT)));
	if (i>0 && j>0 && matrix[i-1][j-1] + 1 == matrix[i][j])
		return backtrace(i-1, j-1, matrix, debug) + (debug ? " rep " : std::string(1, char(REPLACE)));
	if (i>0 && j>0 && matrix[i-1][j-1]  == matrix[i][j])
		return backtrace(i-1, j-1, matrix, debug) + (debug ? " skp " : std::string(1, char(SKIP)));
	return "";
}

std::string backtraceTwd(int i, int j, std::vector<std::vector<int>> matrix, std::string init, std::string target, bool debug)
{
	if(i > 1 && j > 1 && matrix[i-2][j-2]+1 == matrix[i][j]) {
		int initIdx = i-1;
		int targetIdx = j-1;
		bool isTwiddle = init.at(initIdx-1) == target.at(targetIdx) && init.at(initIdx) == target.at(targetIdx-1);

		if(isTwiddle) {
			return backtraceTwd(i-2, j-2, matrix, init, target, debug) + (debug ? " twd " : std::string(1, char(TWIDDLE)));
		}
	}

	//TODO make string of operations to int of operations
	if (i>0 && matrix[i-1][j] + 1 == matrix[i][j])
		return backtraceTwd(i-1, j, matrix, init, target, debug) + (debug ? " del " : std::string(1, char(DELETE)));
	if (j>0 && matrix[i][j-1] + 1 == matrix[i][j])
		return backtraceTwd(i, j-1, matrix, init, target, debug) + (debug ? " ins " : std::string(1, char(INSERT)));
	if (i>0 && j>0 && matrix[i-1][j-1] + 1 == matrix[i][j])
		return backtraceTwd(i-1, j-1, matrix, init, target, debug) + (debug ? " rep " : std::string(1, char(REPLACE)));
	if (i>0 && matrix[i][j] == matrix[i-1][j] && i == init.size() && j == target.size()) {
		//find cut off
		while (i>1 && matrix[i][j] != matrix[i-1][j]+1)
			i--;
		return backtraceTwd(i-1, j, matrix, init, target, debug) + (debug ? " kil " : std::string(1,char(KILL)));
	}
	if (i>0 && j>0 && matrix[i-1][j-1]  == matrix[i][j])
		return backtraceTwd(i-1, j-1, matrix, init, target, debug) + (debug ? " skp " : std::string(1, char(SKIP)));
	return "";
}

void applyKill(std::vector<std::vector<int>>* matrix, std::string init, std::string target) {
	// https://github.com/phillco/Algorithms/blob/master/src/algorithms/AdvancedEditDistance.groovy
	// find cheapest cut-off for Kill
	uint32_t lowIdx = 1;
	uint32_t tl = target.size();
	for (uint32_t i=0; i < init.size();++i) {
		if ((*matrix)[i][tl] < (*matrix)[lowIdx][tl])
			lowIdx = i;
	}
	for (uint32_t i=lowIdx+1;i<=init.size();++i)
		(*matrix)[i][tl] = std::min(1+(*matrix)[lowIdx][tl], (*matrix)[i][tl]);
}
