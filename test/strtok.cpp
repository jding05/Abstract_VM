#include <cstring>
#include <iostream>

int main()
{
	std::string input;
	input += "A bird came down the walk";
	char *cpy_str;//[100];
	char *cpy_str2;//[100];
	std::strcpy(cpy_str, (input).c_str());
	std::strcpy(cpy_str2, input.c_str());
	char * token = std::strtok(cpy_str, " ");
	while (token != NULL)
	{
		std::cout << token << "\n";
		token = std::strtok(NULL, " ");
	}
	std::cout << input << std::endl;
	std::cout << cpy_str << std::endl;
	std::cout << cpy_str2 << std::endl;
	std::cout << "[]" << std::endl;
}

// char *strtok(char *str, const char *delim);
// 1. if str != NULL -> the call is treated as the first call to strtok for the particular stirng,
//			and the funciton seraches for the first character which is not contained in delim.
	// * if no such character was found, there are no tlkens in str at all, the the function return nullpointer;

// 2. if str == NULL, the call is treated as a subsequent calls to strtok; the function continues form
//		where it left in previous invocation.
