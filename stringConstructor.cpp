#include <string>

#include "stringConstructor.hpp"
#include "elementOps.hpp"

void changeExistingStr(std::string *init, std::string target, std::string operations, std::string *iterations)
{
	int initIdx = 0;
	int targetIdx = 0;
	
	if(iterations != nullptr)
		iterations->append(*init).append("\n");
	
	for(int i = 0; i < operations.size(); i++)
	{
		switch(operations[i])
		{
			case SKIP:
				{
					initIdx++;
					targetIdx++;
					break;
				}
			case DELETE:
				{
					Delete(init, initIdx);
					break;
				}
			case INSERT:
				{
					Insert(init, initIdx, target.at(targetIdx));
					initIdx++;
					targetIdx++;
					break;
				}
			case REPLACE:
				{
					Replace(init, initIdx, target.at(targetIdx));
					initIdx++;
					targetIdx++;
					break;
				}
			case TWIDDLE:
				{
					Twiddle(init, initIdx);
					initIdx += 2;
					targetIdx += 2;
					break;
				}
			case KILL:
				{
					Kill(init, initIdx);
					i = operations.size();
					break;
				}
			default: continue;
		}
		
		// get a step by step string 
		if(iterations != nullptr)
			iterations->append(*init).append("\n");
		
	}
}

std::string createNewStr(std::string init, std::string target, std::string operations, std::string *iterations)
{
	std::string result = "";
	
	int initIdx = 0;
	int targetIdx = 0;
	int resultIdx = 0;
	
	for(int i = 0; i < operations.size(); i++)
	{
		switch(operations[i])
		{
			case SKIP:
				{
					// we need to copy the old string if we want to create a word from scratch
					Copy(&result, resultIdx, init, initIdx);
					initIdx++;
					resultIdx++;
					targetIdx++;
					break;
				}
			case DELETE:
				{
					initIdx++;
					break;
				}
			case INSERT:
				{
					Insert(&result, resultIdx, target.at(targetIdx));
					targetIdx++;
					resultIdx++;
					break;
				}
			case REPLACE:
				{
					Replace(&result, resultIdx, target.at(targetIdx));
					initIdx++;
					resultIdx++;
					targetIdx++;
					break;
				}
			case TWIDDLE:
				{
					Copy(&result, resultIdx, init, initIdx+1);
					Copy(&result, resultIdx+1, init, initIdx);
					
					initIdx += 2;
					resultIdx += 2;
					break;
				}
			case KILL:
				{
					i = operations.size();
					break;
				}
			default: continue;
		}
		
		// get a step by step string 
		if(iterations != nullptr)
			iterations->append(result).append("\n");
		
	}
	return result;
}
