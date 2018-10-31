#ifndef RPNCAL_HPP
# define RPNCAL_HPP

# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"
# include <cstdlib>
# include <exception>
# include "IOperand.hpp"
# include "Factory.hpp"
# include "Parser.hpp"

class RPNCal {

public:
	RPNCal();
	RPNCal(Parser const &);
	RPNCal(RPNCal const &);
	RPNCal &operator=(RPNCal const &);
	~RPNCal();

	std::string			getFileName() const;
	std::list<t_Token>	getRPNLexeme() const;

	struct	exit_error : public std::exception
	{
		virtual const char *what(void) const throw();
	};
private:
	eOperandType	_findEOperandType(std::string name);
	std::string		_findNbValue(std::string name, eOperandType type);

	void	_destoryStack();
	void 	_run();

	void	_push(std::list<t_Token>::iterator &);
	void	_pop(std::list<t_Token>::iterator &);
	void	_dump(std::list<t_Token>::iterator &);
	void	_assert(std::list<t_Token>::iterator &);
	void	_add(std::list<t_Token>::iterator &);
	void	_sub(std::list<t_Token>::iterator &);
	void	_mul(std::list<t_Token>::iterator &);
	void	_div(std::list<t_Token>::iterator &);
	void	_mod(std::list<t_Token>::iterator &);
	void	_print(std::list<t_Token>::iterator &);
	void	_exit(std::list<t_Token>::iterator &);

	struct	stack_error : public std::length_error
	{
		stack_error(const char *);
	};
	struct	assert_error : public std::logic_error
	{
		assert_error(const char *);
	};
	struct	print_error : public std::invalid_argument
	{
		print_error(const char *);
	};

	std::list<t_Token>		_rpnlexeme;
	std::string				_fileName;

	std::map<int, void (RPNCal::*)(std::list<t_Token>::iterator &)>	_instruction;
	std::list<IOperand const *>	_stack;
	Factory						_factory;
};

#endif
