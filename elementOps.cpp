#include <iostream>
#include <string>

#include "elementOps.hpp"

void Skip(int *idx)
{
	*idx = *idx + 1;
}

void Copy(std::string *target, int idx, std::string toCopy, int copyIdx)
{
	target->insert(idx, 1, toCopy[copyIdx]);
}

void Delete(std::string *target, int idx)
{
	target->erase(target->begin() + idx);
}

void Insert(std::string *target, int idx, char toInsert)
{
	target->insert(idx, 1, toInsert);
}

void Replace(std::string *target, int idx, char toInsert)
{
	target->replace(idx, 1, 1, toInsert);
}

void Twiddle(std::string *target, int idx)
{
	if(idx < target->size()-1)
	{
		// save char at idx
		std::string temp(1, target->at(idx));
		// delete char at idx
		target->erase(target->begin() + idx);
		// insert char at idx+1
		target->insert(idx+1, temp);
	}
}

void Kill(std::string *target, int idx)
{
	target->erase(target->begin() + idx, target->begin() + target->size());
}
