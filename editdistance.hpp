#include "elementOps.hpp"
#include <vector>
#include <string>

class ED {
public:
	/**
	 * fill 2-dim vactor int with highest column index
	 * @param *matrix (adress of processed matrix)
	 * @param initSize (size of inital char array)
	 * @param targetSize (size of desired char array)
	 */
	void createMatrix(std::vector<std::vector<int>> *matrix, int initSize, int targetSize);

	/**
	 * returns int column of 2-dim matrix
	 * @return (returns most upper right column (min edit distance))
	 */
	int getMinEditDistance(std::vector<std::vector<int>> matrix);

	/**
	 * fills out 2x2 vector matrix with edit distance algorithm
	 * @param twiddle (if true twiddle is included)
	 */
	void fillEditDistance(std::vector<std::vector<int>>* matix, std::string init, std::string target, bool twiddle);

	/**
	 * backtrace from https://de.wikipedia.org/wiki/Levenshtein-Distanz gives back operations in string numbers from 0 to 4
	 * @param debug (if true returns written out word instead of numbers)
	 */
	std::string backtrace(int i, int j, std::vector<std::vector<int>> matrix, bool debug);

	/**
	 * backtrace with twiddle
	 */
	std::string backtraceTwd(int i, int j, std::vector<std::vector<int>> matrix, std::string init, std::string target, bool debug);

	/**
	 * finds optimal cutoff for Kill and corrects Matrix
	 */
	void applyKill(std::vector<std::vector<int>>* matrix, std::string init, std::string target);

	/**
	 * set custom costs for operations
	 */
	void setCost(uint32_t cost[OPERATION_AMOUNT]);
	uint32_t cost[OPERATION_AMOUNT] = {0,1,1,1,1,1};
//private:
};