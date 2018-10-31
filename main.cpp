#include "Lexer.hpp"
#include "Parser.hpp"
#include "RPNCal.hpp"

int main(int argc, char **argv)
{
	try
	{
		Lexer	lex(argc, argv);
		Parser	parse(lex);
		RPNCal	rpn(parse);

		return 0;
	}
	catch (RPNCal::exit_error const &e)
	{
		std::cout << RED << "exit error: " << RESET << e.what() << std::endl;
		std::exit(1);
	}
}
