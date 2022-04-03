/**
 * changes init to target string with the operations from backtrace (non debug)
 * @param *iterations (if !NULL appends step by step operations)
 */
void changeExistingStr(std::string *init, std::string target, std::string operations, std::string *iterations);

/**
 * creates string with the operations from backtrace (non debug)
 * @param *iterations (if !NULL appends step by step operations)
 * @return gives back target basically?
 */
std::string createNewStr(std::string init, std::string target, std::string operations, std::string *iterations);
