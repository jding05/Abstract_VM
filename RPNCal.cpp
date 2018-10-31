#include "RPNCal.hpp"
#include <string>

RPNCal::RPNCal() {}

RPNCal::RPNCal(Parser const & srcs) :
	_rpnlexeme(srcs.getPLexeme()), _fileName(srcs.getFileName())
{
	_instruction[0] = &RPNCal::_push;
	_instruction[1] = &RPNCal::_pop;
	_instruction[2] = &RPNCal::_dump;
	_instruction[3] = &RPNCal::_assert;
	_instruction[4] = &RPNCal::_add;
	_instruction[5] = &RPNCal::_sub;
	_instruction[6] = &RPNCal::_mul;
	_instruction[7] = &RPNCal::_div;
	_instruction[8] = &RPNCal::_mod;
	_instruction[9] = &RPNCal::_print;
	_instruction[10] = &RPNCal::_exit;
	_run();
}

RPNCal::RPNCal(RPNCal const & srcs)
{
	_rpnlexeme = srcs._rpnlexeme;
	_fileName = srcs._fileName;
	_instruction = srcs._instruction;
	_stack = srcs._stack;
	*this = srcs;
}

RPNCal &RPNCal::operator=(RPNCal const & srcs)
{
	_rpnlexeme = srcs._rpnlexeme;
	_fileName = srcs._fileName;
	_instruction = srcs._instruction;
	_stack = srcs._stack;
	return *this;
}

RPNCal::~RPNCal() {}

std::string			RPNCal::getFileName() const
{
	return _fileName;
}

std::list<t_Token>	RPNCal::getRPNLexeme() const
{
	return _rpnlexeme;
}

void	RPNCal::_destoryStack()
{
	for (auto it : _stack)
		delete it;
}

void	RPNCal::_run()
{
	std::string const instructions[] = {"push", "pop", "dump", "assert", "add",
								"sub", "mul", "div", "mod", "print", "exit"};
	for (auto it = _rpnlexeme.begin(); it != _rpnlexeme.end(); it++)
	{
		try
		{
			for (int i = 0; i < 11; i++)
			{
				if (instructions[i] == it->name)
				{
					(this->*_instruction.at(i))(it);
					break;
				}
			}
		}
		catch (std::overflow_error const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31moverflow exception: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);
		}
		catch (std::underflow_error const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31munderflow exception: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);
		}
		catch (std::runtime_error const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31mruntime exception: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);

		}
		catch (RPNCal::stack_error const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31mstack error: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);

		}
		catch (RPNCal::assert_error const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31massert error: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);

		}
		catch (RPNCal::print_error const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31mprint error: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);

		}
		catch (std::exception const &e)
		{
			std::string emsg;
			emsg += _fileName + ":" + std::to_string(it->row);
			emsg += ":" + std::to_string(it->col) + ": ";
			emsg += "\033[1;31mstd::exception: \033[0m";
			emsg += e.what();
			emsg += ": \'\033[1;33m" + it->name + "\033[0m\'";
			std::cout << emsg << std::endl;
			_destoryStack();
			std::exit(1);

		}
	}
	_destoryStack();
	throw RPNCal::exit_error();
}

eOperandType	RPNCal::_findEOperandType(std::string name)
{
	if (name.compare(0, 4, "int8") == 0)
		return Int8;
	else if (name.compare(0, 5, "int16") == 0)
		return Int16;
	else if (name.compare(0, 5, "int32") == 0)
		return Int32;
	else if (name.compare(0, 5, "float") == 0)
		return Float;
	else if (name.compare(0, 6, "double") == 0)
		return Double;
	else
		return Error;
}

std::string	RPNCal::_findNbValue(std::string name, eOperandType type)
{
	std::string tmp(name);
	switch (type)
	{
		case Int8: tmp.erase(0, 5); break;

		case Int16: tmp.erase(0, 6); break;

		case Int32: tmp.erase(0, 6); break;

		case Float: tmp.erase(0, 6); break;

		case Double: tmp.erase(0, 7); break;

		default: return "";
	}
	tmp.erase(tmp.size() - 1, 1);
	return tmp;
}

void	RPNCal::_push(std::list<t_Token>::iterator &it)
{
	it++;
	eOperandType etype = _findEOperandType((*it).name);
	std::string	value = _findNbValue((*it).name, etype);
	_stack.push_front(_factory.createOperand(etype, value));
}

void	RPNCal::_pop(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.size() == 0)
		throw RPNCal::stack_error("pop on empty stack");
	delete _stack.front();
	_stack.pop_front();
}

void	RPNCal::_dump(std::list<t_Token>::iterator &it)
{
	(void)it;
	for (auto sitr : _stack)
		std::cout << sitr->toString() << std::endl;
}

void	RPNCal::_assert(std::list<t_Token>::iterator &it)
{
	it++;
	if (_stack.empty())
		throw stack_error("use assert on empty stack");
	IOperand const*	v = _stack.front();
	eOperandType etype = _findEOperandType((*it).name);
	std::string	value = _findNbValue((*it).name, etype);
	if (v->getType() != etype)
	{
		std::cout << "getType: " << v->getType() << " _findEType: " << _findEOperandType((*it).name) << std::endl;
		throw assert_error("assertion with different type");
	}
	IOperand const* token = _factory.createOperand(etype, value);
	if (v->toString() != token->toString())
	{
		delete token;
		throw assert_error("assertion with different value");
	}
	delete token;
}

void	RPNCal::_add(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.size() < 2)
		throw RPNCal::stack_error("stack is too small to add");
	IOperand const *lv = _stack.front();
	_stack.pop_front();
	IOperand const *rv = _stack.front();
	_stack.pop_front();
	try
	{
		_stack.push_front(*lv + *rv);
	}
	catch (std::overflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::exception const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	delete lv;
	delete rv;
}

void	RPNCal::_sub(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.size() < 2)
		throw RPNCal::stack_error("stack is too small to sub");
	IOperand const *lv = _stack.front();
	_stack.pop_front();
	IOperand const *rv = _stack.front();
	_stack.pop_front();
	try
	{
		_stack.push_front(*lv - *rv);
	}
	catch (std::overflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::exception const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	delete lv;
	delete rv;
}

void	RPNCal::_mul(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.size() < 2)
		throw RPNCal::stack_error("stack is too small to sub");
	IOperand const *lv = _stack.front();
	_stack.pop_front();
	IOperand const *rv = _stack.front();
	_stack.pop_front();
	try
	{
		_stack.push_front(*lv * *rv);
	}
	catch (std::overflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::exception const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	delete lv;
	delete rv;
}

void	RPNCal::_div(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.size() < 2)
		throw RPNCal::stack_error("stack is too small to sub");
	IOperand const *lv = _stack.front();
	_stack.pop_front();
	IOperand const *rv = _stack.front();
	_stack.pop_front();
	try
	{
		_stack.push_front(*lv / *rv);
	}
	catch (std::runtime_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::overflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::exception const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	delete lv;
	delete rv;
}

void	RPNCal::_mod(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.size() < 2)
		throw RPNCal::stack_error("stack is too small to sub");
	IOperand const *lv = _stack.front();
	_stack.pop_front();
	IOperand const *rv = _stack.front();
	_stack.pop_front();
	try
	{
		_stack.push_front(*lv % *rv);
	}
	catch (std::runtime_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::overflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	catch (std::exception const & e)
	{
		delete lv;
		delete rv;
		throw e;
	}
	delete lv;
	delete rv;
}

void	RPNCal::_print(std::list<t_Token>::iterator &it)
{
	(void)it;
	if (_stack.empty())
		throw stack_error("print on empty stack");
	if (_stack.front()->getType() != Int8)
		throw print_error("print on non 8-bit integer");
	int res = std::stoi(_stack.front()->toString());
	std::cout << static_cast<char>(res) << std::endl;
}

void	RPNCal::_exit(std::list<t_Token>::iterator &it)
{
	(void)it;
	std::exit(0);
}

RPNCal::stack_error::stack_error(const char *emsg):
	std::length_error(emsg) {}

RPNCal::assert_error::assert_error(const char *emsg):
	std::logic_error(emsg) {}

RPNCal::print_error::print_error(const char *emsg):
	std::invalid_argument(emsg) {}

const char *RPNCal::exit_error::what(void) const throw()
{
	return ("absent of \'\033[1;33mexit\033[0m\' instruction");
}
