//
// Macros
//
#ifdef __unix__
	#define OS_windows 0
#elif defined(_WIN32) || defined(WIN32)
	#define OS_windows 1
	#include <windows.h>
#endif

/**
 * define colors for printfColor function
 */
#ifdef __unix__
	#define GREEN 32
#elif defined(_WIN32) || defined(WIN32)
	#define GREEN 2
#endif

/**
 * printf with a color parameter
 * @param color (index of color)
 * @param *format ... (printf params)
 */
void printfColor(int color, const char *format, ...);

/**
 * prints editdistance in cmd in column style
 * @param matrix (vector with numbers)
 * @param init (initial word)
 * @param target (goal word)
 */
void printEditDistance(std::vector<std::vector<int>> matrix, std::string init, std::string target);

/**
 * prints real operations in readable format
 * @param operations (operations in non debug format)
 */
void printOperations(std::string operations);
