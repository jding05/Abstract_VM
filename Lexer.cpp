#include "Lexer.hpp"

Lexer::Lexer(): _error(false) {}

Lexer::Lexer(int argc, char **argv): _pflag(false), _error(false)
{
	if (argc > 2 && std::strcmp(argv[1], "-p"))
	{
		std::cout << "Usage: ./avm [-ph] [filename]" << std::endl;
		std::exit(0);
	}
	else if (argc == 2 &&
	(!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")))
	{
		std::cout << "Usage: ./avm [-ph] [filename]" << std::endl;
		_showValidInstruction();
		std::exit(0);
	}
	else if (argc == 1)
	{
		_fileName = "stdin";
		_tokenization(std::cin);
	}
	else
	{
		int i = 1;
		if (argc == 3)
		{
			_pflag = true;
			i++;
		}
		_fileName = argv[i];
		std::ifstream fileReadin(_fileName);
		if (fileReadin.is_open())
		{
			_tokenization(fileReadin, 3);
			fileReadin.close();
		}
		else
		{
			std::cout << "Error: " << argv[i] << ": open file failed" << std::endl;
			_error = true;
			std::exit(1);
		}
	}
}

Lexer::Lexer(Lexer const & srcs)
{
	_error = srcs._error;
	_errorList = srcs._errorList;
	_lexeme = srcs._lexeme;
	*this = srcs;
}

Lexer &Lexer::operator=(Lexer const & srcs)
{
	_error = srcs._error;
	_errorList = srcs._errorList;
	_lexeme = srcs._lexeme;
	return *this;
}

Lexer::~Lexer() {}

bool	Lexer::getError() const
{
	return _error;
}

std::list<std::string>	Lexer::getErrorList() const
{
	return _errorList;
}

std::list<t_Token>	Lexer::getLexeme() const
{
	return _lexeme;
}

std::string			Lexer::getFileName() const
{
	return _fileName;
}

void	Lexer::_showValidInstruction()
{
	std::cout << "-p           print out the file content (with nl as newline at the end) [not Available for stdin]" << std::endl;
	std::cout << "-h/--help    print out guideline" << std::endl;
	std::cout << std::endl;
	std::cout << "Available Command | Available Number Value " << std::endl;
	std::cout << "------------------+------------------------" << std::endl;
	std::cout << " push             | int8(nb)" << std::endl;
	std::cout << " pop              | int16(nb)" << std::endl;
	std::cout << " dump             | int32(nb)" << std::endl;
	std::cout << " assert           | float(nb)" << std::endl;
	std::cout << " add              | double(nb)" << std::endl;
	std::cout << " sub              | " << std::endl;
	std::cout << " mul              | " << std::endl;
	std::cout << " div              | " << std::endl;
	std::cout << " mod              | " << std::endl;
	std::cout << " print            | " << std::endl;
	std::cout << " exit             | " << std::endl;
}

t_Token	Lexer::_setTokenVar(std::string token, int col, int row, TokenName type)
{
	t_Token	t;

	t.type = type;
	t.name = token;
	t.row = row;
	t.col = col;
	return t;
}

void	Lexer::_generateError(char *token, int row, int col)
{
	std::string emsg;

	emsg += _fileName + ":" + std::to_string(row) + ":" + std::to_string(col);
	emsg += ": ";
	emsg += "\033[1;31mLexical Error: \033[0m";
	emsg += "unknown identifier \'\033[1;33m" + std::string(token) + "\033[0m\'";
	_errorList.push_back(emsg);
}

void	Lexer::_printErrorList()
{
	for (auto it = _errorList.begin(); it != _errorList.end(); it++)
		std::cout << *it << std::endl;
	std::exit(1);
}

void	Lexer::_storeToken(char *token, int row, int col)
{
	std::regex	base_regex;
	std::cmatch	base_match;

	for (auto itr = _lexemeFormat.begin(); itr != _lexemeFormat.end(); itr++)
	{
		base_regex = itr->first;
		if (std::regex_match(token , base_match, base_regex) == true)
		{
			_lexeme.push_back(_setTokenVar(token, col + 1, row, itr->second));
			return ;
		}
	}
	_error = true;
	_generateError(token, row, col);
}

void	Lexer::_getTokenCol(char *cpy_str, int &col)
{
	if (col != -1)
		while (cpy_str[++col] && cpy_str[col] != ' ' && cpy_str[col] != '\t');
	while (cpy_str[++col] && (cpy_str[col] == ' ' || cpy_str[col] == '\t'));
}

void	Lexer::_strtrim(char *copy_str)
{
	int idx = -1, check = 0;

	while (copy_str[++idx])
	{
		if (copy_str[idx] == ';' || check == 1)
		{
			copy_str[idx] = '\0';
			check = 1;
		}
	}
}

void	Lexer::_printLexeme()
{
	int i = -1;
	std::cout << "==============================================" << std::endl;
	for (auto itr = _lexeme.begin(); itr != _lexeme.end(); itr++)
	{
		if (++i == 0)
			std::cout << "row " << itr->row << ": ";
		std::cout << itr->name << " ";
		if (itr->name == "nl")
		{
			std::cout << std::endl;
			i = -1;
		}
	}
	std::cout << "==============================================" << std::endl;
}

void	Lexer::_tokenization(std::istream & stream, int fd)
{
	std::string	line;
	char		*copy_str;
	char		*tokens;
	int			row = 0, col;

	while (getline(stream, line))
	{
		row++;
		if (fd == 0 && std::string(line) == ";;")
		{
			if (_error)
				_printErrorList();
			return ;
		}
		copy_str = new char [ line.size() + 1 ];
		std::strcpy(copy_str, line.c_str());
		_strtrim(copy_str);
		tokens = std::strtok(copy_str, " \t");
		col = -1;
		while (tokens != NULL)
		{
			_getTokenCol(copy_str, col);
			_storeToken(tokens, row, col);
			tokens = std::strtok(NULL, " ");
		}
		if (_lexeme.size() > 0)
			_lexeme.push_back(_setTokenVar("nl", col, row, TokenName::NL));
		delete [] copy_str;
	}
	if (_pflag == true)
		_printLexeme();
	if (_error)
		_printErrorList();
}

std::map<std::string, TokenName>Lexer::_lexemeFormat =
{
	{"push|pop|dump|assert|add|sub|mul|div|mod|print|exit", TokenName::INSTR},
	{"int(8|16|32)\\(([-]?[0-9]+)\\)|(double|float)\\(([-]?[0-9]+\\.[0-9]+)\\)", TokenName::VALUE}
};
