#include "editdistance.hpp"
#include "elementOps.hpp"

#include <vector>
#include <string>
#include <algorithm>

void createMatrix(std::vector<std::vector<int>> *matrix, int initSize, int goalSize)
{
	for(int i = 0; i < initSize+1; i++)
	{
		std::vector<int> temp;
		for(int j = 0; j < goalSize+1; j++)
		{
			if(i > j) temp.push_back(i);	
			else temp.push_back(j);
		}
		matrix->push_back(temp);
	}
}

// TODO Add comments cleanup
// TODO change *matrix to &matrix
void fillEditDistance(std::vector<std::vector<int>>& matrix, std::string init, std::string target, bool twiddle)
{
	int k = 0;
	
	for(int i = 0; i < matrix.size(); i++)
	{
		// we already have the result for the empty string so skip first line
		if(i == 0) continue;
		
		//std::vector<int> temp;
		
		for(int j = 0; j < matrix[i].size(); j++)
		{
			if(j == 0) matrix[i][j] = i;
			else
			{
				// algorithm
				//temp.push_back(matrix->at(i-1).at(j) + 1); // del
				matrix[i][j] = matrix[i-1][j]+1; // del

				//if(temp.at(j-1) + 1 < temp.back())
				if(matrix[i][j-1] + 1 < matrix[i][j])
				{
					//temp.pop_back();
					//temp.push_back(temp.at(j-1) + 1); // ins
					matrix[i][j] = matrix[i][j-1] + 1; //ins
				}
				
				if(init.at(i-1) == target.at(j-1)) k = 0;
				else k = 1;
				
				//if(matrix->at(i-1).at(j-1) + k < temp.back())
				if(matrix[i-1][j-1] + k < matrix[i][j])
				{
					//temp.pop_back();							// k = 1 rep
					//temp.push_back(matrix->at(i-1).at(j-1)+k);	// k = 0 skp
					matrix[i][j] = matrix[i-1][j-1]+k;	// k = 0 skp
				}
				
				// twiddle
				if(twiddle) // && k == 1)
				{
					if (i <= init.size() && j <= target.size() && i > 1 && j > 1)
					{
						// remember that index 0 is the empty word, so our word starts at index 1
						if(init.at(i-2) == target.at(j-1) && init.at(i-1) == target.at(j-2))
						{
							//temp.pop_back();
							//temp.push_back(matrix->at(i-1).at(j-1));
							//TODO check for cost
							matrix[i][j] = matrix[i-1][j-1];
						}
					}
				}
			}
		}
		
		// insert the new row at position i
		//matrix->insert(matrix->begin() + i, temp);
		// delete old row
		//matrix->erase(matrix->begin() + i + 1);
	}
//	// find cheapest cut-off for Kill
//	uint32_t lowIdx = 1;
//	uint32_t tl = target.size();
//	for (uint32_t i=0; i < init.size();++i) {
//		if (matrix[i][tl] < matrix[lowIdx][tl])
//			lowIdx = i;
//	}
//	matrix[init.size()][tl] = std::min(1+matrix[lowIdx][tl], matrix[init.size()][tl]);
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
	// matrix is always size+1
	int initIdx = i-1;
	int targetIdx = j-1;
	
	if(initIdx >= 1 && targetIdx >= 1)
	{
		bool isTwiddle = init.at(initIdx-1) == target.at(targetIdx) && init.at(initIdx) == target.at(targetIdx-1);

		if(isTwiddle && matrix[i-1][j-1] == matrix[i][j])
		{
			return backtraceTwd(i-2, j-2, matrix, init, target, debug) + (debug ? " twd " : std::string(1, char(TWIDDLE)));
		}
	}

	if (i>0 && matrix[i-1][j] + 1 == matrix[i][j])
		return backtraceTwd(i-1, j, matrix, init, target, debug) + (debug ? " del " : std::string(1, char(DELETE)));
	if (j>0 && matrix[i][j-1] + 1 == matrix[i][j])
		return backtraceTwd(i, j-1, matrix, init, target, debug) + (debug ? " ins " : std::string(1, char(INSERT)));
	if (i>0 && j>0 && matrix[i-1][j-1] + 1 == matrix[i][j])
		return backtraceTwd(i-1, j-1, matrix, init, target, debug) + (debug ? " rep " : std::string(1, char(REPLACE)));
	if (i>0 && j>0 && matrix[i-1][j-1]  == matrix[i][j])
		return backtraceTwd(i-1, j-1, matrix, init, target, debug) + (debug ? " skp " : std::string(1, char(SKIP)));
	return "";
}

// TODO check corecctness, implementation in matrix algorithm
void detectKill(std::string *operations)
{
	int deleteAmount = 0;
	// detect 2 or more delete
	for(int i = operations->size()-1; i >= 0; i--)
	{
		if(operations->at(i) == DELETE) deleteAmount++;
		else break;
	}
	
	if(deleteAmount > 1)
	{
		operations->erase(operations->size()-deleteAmount, deleteAmount);
		operations->append(std::string(1, char(KILL)));
	}
}
