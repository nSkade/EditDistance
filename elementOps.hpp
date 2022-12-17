#include <string>

enum OPERATIONS
{
	SKIP = 0,
	DELETE,
	INSERT,
	REPLACE,
	TWIDDLE,
	KILL,
	OPERATION_AMOUNT
};

/**
 * (for creating a new word)
 * @param *target (adress of changing string)
 * @param idx (position in target)
 * @param toCopy (string wich includes char to copy)
 * @param copyIdx (position in toCopy)
 */
void Copy(std::string *target, int idx, std::string toCopy, int copyIdx);

void Delete(std::string *target, int idx);
void Insert(std::string *target, int idx, char toInsert);
void Replace(std::string *target, int idx, char toInsert);

void Twiddle(std::string *target, int idx);
void Kill(std::string *target, int idx);
