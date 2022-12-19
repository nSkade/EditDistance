#include "editdistance.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>

void ED::createMatrix(std::vector<std::vector<int>>* matrix, int initSize, int goalSize)
{
	(*matrix) = std::vector<std::vector<int>>(initSize+1,std::vector<int>(goalSize+1,0));
	for(int i = 0; i < initSize+1; i++)
	{
		for(int j = 0; j < goalSize+1; j++)
		{
			(*matrix)[i][j] = 0;
			if (i==0)
				(*matrix)[i][j] = j*cost[ED_INSERT];
			if (j==0)
				(*matrix)[i][j] = i*cost[ED_INSERT];
		}
	}
}
void ED::fillEditDistance(std::vector<std::vector<int>>* matrix, std::string init, std::string target, bool twiddle)
{
	int k = 0;
	for(int i = 0; i < (*matrix).size(); i++) {
		// we already have the result for the empty string so skip first line
		if(i == 0) continue;
		
		for(int j = 0; j < (*matrix)[i].size(); j++) {
			if(j == 0) {
				continue;
			}
			(*matrix)[i][j] = (*matrix)[i-1][j]+cost[ED_DELETE]; // del

			if((*matrix)[i][j-1] + cost[ED_INSERT] < (*matrix)[i][j]) {
				(*matrix)[i][j] = (*matrix)[i][j-1] + cost[ED_INSERT]; //ins
			}
			
			if(init.at(i-1) == target.at(j-1)) k = cost[ED_SKIP];
			else k = cost[ED_REPLACE];
			
			if((*matrix)[i-1][j-1] + k < (*matrix)[i][j]) {
				// k = 1 rep // k = 0 skp
				(*matrix)[i][j] = (*matrix)[i-1][j-1]+k;
			}
			
			// twiddle
			if (twiddle && i <= init.size() && j <= target.size() && i > 1 && j > 1) {
				if((*matrix)[i-2][j-2]+cost[ED_TWIDDLE] < (*matrix)[i][j]) {
					// remember that index 0 is the empty word, so our word starts at index 1
					if(init.at(i-2) == target.at(j-1) && init.at(i-1) == target.at(j-2)) {
						//TODO check for cost
						(*matrix)[i][j] = (*matrix)[i-2][j-2]+cost[ED_TWIDDLE];
					}
				}
			}
		}
	}
}

int ED::getMinEditDistance(std::vector<std::vector<int>> matrix)
{
	int i = matrix.size();
	int j = matrix[i-1].size();
	
	return matrix[i-1][j-1];
}

std::string ED::backtrace(int i, int j, std::vector<std::vector<int>> matrix, bool debug)
{
//	ED_OP op = OPERATION_AMOUNT; //invalid
//	uint32_t mcost = UINT32_MAX;
//
//	if (i>0 && matrix[i-1][j] + cost[ED_DELETE] == matrix[i][j]) {
//		mcost = matrix[i-1][j];
//		op = ED_DELETE;
//	}
	if (i>0 && matrix[i-1][j] + cost[ED_DELETE] == matrix[i][j])
		return backtrace(i-1, j, matrix, debug) + (debug ? " del " : std::string(1, char(ED_DELETE)));
	if (j>0 && matrix[i][j-1] + cost[ED_INSERT] == matrix[i][j])
		return backtrace(i, j-1, matrix, debug) + (debug ? " ins " : std::string(1, char(ED_INSERT)));
	if (i>0 && j>0 && matrix[i-1][j-1] + cost[ED_REPLACE] == matrix[i][j])
		return backtrace(i-1, j-1, matrix, debug) + (debug ? " rep " : std::string(1, char(ED_REPLACE)));
	if (i>0 && j>0 && matrix[i-1][j-1] + cost[ED_SKIP] == matrix[i][j])
		return backtrace(i-1, j-1, matrix, debug) + (debug ? " skp " : std::string(1, char(ED_SKIP)));

//	if (op == ED_DELETE)
//		return backtrace(i-1, j, matrix, debug) + (debug ? " del " : std::string(1, char(ED_DELETE)));
//	if (op == ED_INSERT)
//		return backtrace(i, j-1, matrix, debug) + (debug ? " ins " : std::string(1, char(ED_INSERT)));
//	if (op == ED_REPLACE)
//		return backtrace(i-1, j-1, matrix, debug) + (debug ? " rep " : std::string(1, char(ED_REPLACE)));
//	if (op == ED_SKIP)
//		return backtrace(i-1, j-1, matrix, debug) + (debug ? " skp " : std::string(1, char(ED_SKIP)));
	return "";
}

std::string ED::backtraceTwd(int i, int j, std::vector<std::vector<int>> matrix, std::string init, std::string target, bool debug)
{
	if(i > 1 && j > 1 && matrix[i-2][j-2]+cost[ED_TWIDDLE] == matrix[i][j]) {
		int initIdx = i-1;
		int targetIdx = j-1;
		bool isTwiddle = init.at(initIdx-1) == target.at(targetIdx) && init.at(initIdx) == target.at(targetIdx-1);

		if(isTwiddle) {
			return backtraceTwd(i-2, j-2, matrix, init, target, debug) + (debug ? " twd " : std::string(1, char(ED_TWIDDLE)));
		}
	}

	if (i>0 && matrix[i-1][j] + cost[ED_DELETE] == matrix[i][j])
		return backtraceTwd(i-1, j, matrix, init, target, debug) + (debug ? " del " : std::string(1, char(ED_DELETE)));
	if (j>0 && matrix[i][j-1] + cost[ED_INSERT] == matrix[i][j])
		return backtraceTwd(i, j-1, matrix, init, target, debug) + (debug ? " ins " : std::string(1, char(ED_INSERT)));
	if (i>0 && j>0 && matrix[i-1][j-1] + cost[ED_REPLACE] == matrix[i][j])
		return backtraceTwd(i-1, j-1, matrix, init, target, debug) + (debug ? " rep " : std::string(1, char(ED_REPLACE)));
	if (i>0 && matrix[i][j] == matrix[i-1][j] && i == init.size() && j == target.size()) {
		//find cut off
		while (i>1 && matrix[i][j] != matrix[i-1][j]+cost[ED_KILL])
			i--;
		return backtraceTwd(i-1, j, matrix, init, target, debug) + (debug ? " kil " : std::string(1,char(ED_KILL)));
	}
	if (i>0 && j>0 && matrix[i-1][j-1] + cost[ED_SKIP] == matrix[i][j])
		return backtraceTwd(i-1, j-1, matrix, init, target, debug) + (debug ? " skp " : std::string(1, char(ED_SKIP)));
	return "";
}

void ED::applyKill(std::vector<std::vector<int>>* matrix, std::string init, std::string target) {
	// https://github.com/phillco/Algorithms/blob/master/src/algorithms/AdvancedEditDistance.groovy
	// find cheapest cut-off for Kill
	uint32_t lowIdx = 1;
	uint32_t tl = target.size();
	for (uint32_t i=0; i < init.size();++i) {
		if ((*matrix)[i][tl] < (*matrix)[lowIdx][tl])
			lowIdx = i;
	}
	for (uint32_t i=1;i<=init.size();++i)
		(*matrix)[i][tl] = std::min((*matrix)[lowIdx][tl]+int(cost[ED_KILL]), (*matrix)[i][tl]);
}

void ED::setCost(uint32_t cost[OPERATION_AMOUNT]) {
	memcpy(this->cost,cost,OPERATION_AMOUNT*sizeof(cost[0]));
}
