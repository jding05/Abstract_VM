#include "Factory.hpp"
#include "Operand.hpp"
#include <iostream>

Factory::Factory() {}
Factory::Factory( Factory const & srcs ) { *this = srcs; }
Factory &Factory::operator=( Factory const & srcs ) { (void)srcs; return *this; }
Factory::~Factory() {}

IOperand const * (Factory::*(Factory::funcPtr[]))(std::string const &) const =
{
	&Factory::createInt8,
	&Factory::createInt16,
	&Factory::createInt32,
	&Factory::createFloat,
	&Factory::createDouble
};

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	return (this->*funcPtr[type])(value);
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	std::stringstream	s(value);
	double				res;

	s >> res;
	if (res < std::numeric_limits<char>::min())
		throw (std::underflow_error("failed to create int8"));
	if (res > std::numeric_limits<char>::max())
		throw (std::overflow_error("failed to create int8"));
	return new Operand<char>(static_cast<char>(res), eOperandType::Int8, this);
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	std::stringstream	s(value);
	double				res;

	s >> res;
	if (res < std::numeric_limits<short>::min())
		throw (std::underflow_error("failed to create int16"));
	if (res > std::numeric_limits<short>::max())
		throw (std::overflow_error("failed to create int16"));
	return new Operand<short>(static_cast<short>(res), eOperandType::Int16, this);
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	std::stringstream	s(value);
	double				res;

	s >> res;
	if (res < std::numeric_limits<int>::min())
		throw (std::underflow_error("failed to create int32"));
	if (res > std::numeric_limits<int>::max())
		throw (std::overflow_error("failed to create int32"));
	return new Operand<int>(static_cast<int>(res), eOperandType::Int32, this);
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	std::stringstream	s(value);
	long double				res;

	s >> res;
	if (res < std::numeric_limits<float>::min())
		throw (std::underflow_error("failed to create float"));
	if (res > std::numeric_limits<float>::max())
		throw (std::overflow_error("failed to create float"));
	return new Operand<float>(static_cast<float>(res), eOperandType::Float, this);
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	std::stringstream	s(value);
	long double				res;

	s >> res;
	if (res < std::numeric_limits<double>::min())
		throw (std::underflow_error("failed to create double"));
	if (res > std::numeric_limits<double>::max())
		throw (std::overflow_error("failed to create double"));
	return new Operand<double>(static_cast<double>(res), eOperandType::Double, this);
}
