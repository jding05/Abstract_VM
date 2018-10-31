#ifndef PARSER_HPP
# define PARSER_HPP

#include <cstdlib>
#include "Lexer.hpp"

class Parser {

public:
	Parser();
	Parser(Lexer const &);
	Parser(Parser const &);
	Parser &operator=(Parser const &);
	~Parser();
	bool					getError();
	std::list<std::string>	getErrorList();
	std::list<t_Token>		getPLexeme() const;
	std::string				getFileName() const;


private:
	void	_generateError(std::list<t_Token>::iterator &);
	void	_printErrorList();
	void	_parsing();
	void	_printPLexeme();

	bool					_error;
	std::list<std::string>	_errorList;
	std::list<t_Token>		_plexeme;
	std::string				_fileName;
};

#endif
