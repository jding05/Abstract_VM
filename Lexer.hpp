#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <list>
# include <regex>
# include <map>
# include <fstream>

enum TokenName { INSTR, VALUE, NL };

typedef struct	s_Token {
	TokenName	type;
	std::string	name;
	int			row;
	int			col;
}				t_Token;

class Lexer {

public:
	Lexer();
	Lexer(int, char**);
	Lexer(Lexer const &);
	Lexer &operator=(Lexer const &);
	~Lexer();

	bool					getError() const;
	std::list<std::string>	getErrorList() const;
	std::list<t_Token>		getLexeme() const;
	std::string				getFileName() const;

private:
	void	_showValidInstruction();
	void	_printLexeme();
	t_Token	_setTokenVar(std::string, int, int, TokenName);
	void	_strtrim(char*);
	void	_getTokenCol(char*, int&);
	void	_storeToken(char*, int, int);
	void	_tokenization(std::istream &, int fd = 0);
	void	_generateError(char*, int, int);
	void	_printErrorList();

	std::string				_fileName;
	bool					_pflag;
	bool					_error;
	std::list<std::string>	_errorList;
	std::list<t_Token>		_lexeme;
	static std::map<std::string, TokenName> _lexemeFormat;
};

#endif
