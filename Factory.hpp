#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "IOperand.hpp"
# include <limits>
# include <exception>
# include <sstream>

class Factory {

public:
	Factory();
	Factory( Factory const & );
	Factory &operator=( Factory const & );
	~Factory();

	static IOperand const *(Factory::*funcPtr[])(std::string const &) const;
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

#endif
