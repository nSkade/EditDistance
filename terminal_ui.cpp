#include <iostream>
#include <vector>
#include <string>
#include <stdarg.h>

#include "terminal_ui.hpp"

void printfColor(int color, const char *format, ...)
{
	va_list arg;
	va_start (arg, format);

	#if OS_windows == 1
	{
			CONSOLE_SCREEN_BUFFER_INFO Info;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			vprintf(format, arg);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Info.wAttributes);
	}
	#else
	{
		std::string formatStr(format);
		std::string temp = std::to_string(color);
		std::string newFormat("\x1B[");
		newFormat.append(temp).append("m");
		newFormat.append(formatStr);
		vprintf(newFormat.c_str(), arg);
		printf("\x1B[0m");
	}
	#endif

	va_end (arg);
}

void printEditDistance(std::vector<std::vector<int>> matrix, std::string init, std::string target)
{
	for(int i = matrix.size()-1; i >= 0; i--)
	{
		// print initWord
		if (i > 0) printf("%c", init[i - 1]);
		else printf(" ");

		// print matrix
		for(int j = 0; j < matrix[i].size(); j++)
		{
			printf("|");
			if(matrix[i][j] < 10) printf(" ");

			if(i == j) printfColor(GREEN, "%d", matrix[i][j]);
			else printf("%d", matrix[i][j]);
		}

		// print lines between rows
		printf("\n");
		for(int j = 0; j < matrix[i].size(); j++)
		{
			if(j == 0) printf("-");
			else printf("--");
			printf("|");
		}
		printf("--");
		printf("\n");
	}

	// print Goal word
	printf("    ");
	for(int j = 0; j < target.size(); j++)
	{
		printf("| ");
		printf("%c", target[j]);
	}
	printf("\n");
}

void printOperations(std::string operations)
{
	printf("operations: ");
	for(int i = 0; i < operations.size(); i++)
	{
		printf("%c", operations[i]+'0');
	}
	printf("\n");
}
