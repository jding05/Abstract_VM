#include <string>
#include <iostream>
int main()
{
	std::string s("123456789)");

	std::cout << "before erase:" << s << " size:" << s.size() << std::endl;
	s.erase(0, 5);
	s.erase(s.size() -1, 1);
	std::cout << "after erase:" << s << " size: " << s.size() << std::endl;
}
