#include <fstream>
#include <iostream>
#include <fsntl.h>

void	read(std::istream& is)
{
	std::string line;
	while (getline(is, line))
		sted::cout << line << std::endl;
}

int main(int argc, char **argv)
{
	if (argc == 1)
		read(std::cin);
	else
	{
		std::ifstream fin("txt");
		// std::ifstream fin("txt", std::ifstream::in);
		int fd1 = open("haha", O_RDONLY);
		std::cout << fd1 << std::endl;
		if (fin.is_open())
		{
			int fd2 = open("baba", O_RDONLY);
			std::cout << fd2 << std::endl;
			read(fin);
		}
		else
			std::cout << "cannot be open" <<  std::endl;
	}
}
