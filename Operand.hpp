#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <sstream>
# include <exception>
# include <cmath>
# include <iostream>
# include "Factory.hpp"
# include "IOperand.hpp"


template <typename T>
class Operand : public IOperand {

public:

	Operand<T>( T value, eOperandType type , const Factory *factory ):
		_value(value) ,_str( std::string(std::to_string(value))), _type(type), _factory(factory) {}
	virtual ~Operand<T>(void) {}
	int getPrecision( void ) const
	{
		return _type;
	} // Precision of the type of the instance
	eOperandType getType( void ) const
	{
		return _type;
	} // Type of the instance
	std::string const & toString( void ) const
	{
		return _str;
	}; // String representation of the instance
	IOperand const * operator+( IOperand const & rhs ) const
	{
		std::stringstream sr(toString());
		std::stringstream sl(rhs.toString());

		eOperandType precision = _type > rhs.getType() ? _type : rhs.getType();
		if (precision < Float)
		{
			double lv;
			sl >> lv;
			double rv;
			sr >> rv;
			return _factory->createOperand(precision, std::to_string(lv + rv));
		}
		else
		{
			long double lv;
			sl >> lv;
			long double rv;
			sr >> rv;
			return _factory->createOperand(precision, std::to_string(lv + rv));
		}

	} // Sum
	IOperand const * operator-( IOperand const & rhs ) const
	{
		std::stringstream sr(toString());
		std::stringstream sl(rhs.toString());

		eOperandType precision = _type > rhs.getType() ? _type : rhs.getType();
		double lv;
		sl >> lv;
		double rv;
		sr >> rv;
		return _factory->createOperand(precision, std::to_string(lv - rv));
	}; // Difference
	IOperand const * operator*( IOperand const & rhs ) const
	{
		std::stringstream sr(toString());
		std::stringstream sl(rhs.toString());

		eOperandType precision = _type > rhs.getType() ? _type : rhs.getType();
		if (precision < Float)
		{
			double lv;
			sl >> lv;
			double rv;
			sr >> rv;
			return _factory->createOperand(precision, std::to_string(lv * rv));
		}
		else
		{
			long double lv;
			sl >> lv;
			long double rv;
			sr >> rv;
			return _factory->createOperand(precision, std::to_string(lv * rv));
		}
	}; // Product
	IOperand const * operator/( IOperand const & rhs ) const
	{
		std::stringstream sr(toString());
		std::stringstream sl(rhs.toString());

		eOperandType precision = _type > rhs.getType() ? _type : rhs.getType();
		double lv;
		sl >> lv;
		double rv;
		sr >> rv;
		if (rv == 0)
			throw (std::runtime_error("divide by zero"));
		std::cout << "rv: " << rv << std::endl;
		return _factory->createOperand(precision, std::to_string(lv / rv));
	}; // Quotient
	IOperand const * operator%( IOperand const & rhs ) const
	{
		std::stringstream sr(toString());
		std::stringstream sl(rhs.toString());

		eOperandType precision = _type > rhs.getType() ? _type : rhs.getType();
		double lv;
		sl >> lv;
		double rv;
		sr >> rv;
		if (rv == 0)
			throw (std::runtime_error("modulo by zero"));
		return _factory->createOperand(precision, std::to_string(std::fmod(lv, rv)));
	}; // Modulo


private:
	Operand<T>();
	Operand<T>(Operand<T> const &);
	Operand<T> &operator=(Operand<T> const &);

	T const				_value;
	std::string   		_str;
	eOperandType		_type;
	const Factory *		_factory;
};

#endif
