#include "Parser.hpp"

Parser::Parser(): _error(false) {}

Parser::Parser(Lexer const & srcs) :
	_error(false), _plexeme(srcs.getLexeme()), _fileName(srcs.getFileName())
{
	_parsing();
}

Parser::Parser(Parser const & srcs)
{
	_error = srcs._error;
	_errorList = srcs._errorList;
	_plexeme = srcs._plexeme;
	_fileName = srcs._fileName;
}

Parser &Parser::operator=(Parser const & srcs)
{
	_error = srcs._error;
	_errorList = srcs._errorList;
	_plexeme = srcs._plexeme;
	_fileName = srcs._fileName;
	return *this;
}

Parser::~Parser() {}

bool	Parser::getError()
{
	return _error;
}

std::list<std::string>	Parser::getErrorList()
{
	return _errorList;
}

std::list<t_Token>	Parser::getPLexeme() const
{
	return _plexeme;
}

std::string			Parser::getFileName() const
{
	return _fileName;
}

void	Parser::_generateError(std::list<t_Token>::iterator &it)
{
	std::string emsg;

	emsg += _fileName + ":" + std::to_string((*it).row);
	emsg += ":" + std::to_string((*it).col);
	emsg += ": ";
	emsg += "\033[1;31mParser Error: \033[0m";
	emsg += "too many arguments: ";
	emsg += "\'\033[1;33m" + (*it).name + "\033[0m\'";
	emsg += "-> should change line for this instruction";
	_errorList.push_back(emsg);
}

void	Parser::_printErrorList()
{
	for (auto it = _errorList.begin(); it != _errorList.end(); it++)
		std::cout << *it << std::endl;
	std::exit(1);
}

void	Parser::_printPLexeme()
{
	int i = 0;
	for (auto itr = _plexeme.begin(); itr != _plexeme.end(); itr++)
	{
		std::cout << itr->name << std::endl;
		i++;
	}
}

void	Parser::_parsing()
{
	int i;

	std::string const instructions[] = {"push", "pop", "dump", "assert", "add",
								"sub", "mul", "div", "mod", "print", "exit"};
	for (auto itr = _plexeme.begin(); itr != _plexeme.end(); itr++)
	{
		i = -1;
		while (++i < 11)
		{
			if (instructions[i] == itr->name)
			{
				if (itr->name == "assert" || itr->name == "push")
					itr++;
				itr++;
				break;
			}
		}
		if (itr->name != "nl" && itr->name != "end")
		{
			_error = true;
			_generateError(itr);
			while (itr->name != "nl" && itr->name != "end")
				itr++;
		}
		if (itr->name == "nl")
		{
			itr = _plexeme.erase(itr);
			itr--;
		}
		if (itr->name == "end")
			break ;
	}
	if (_error)
		_printErrorList();
}
