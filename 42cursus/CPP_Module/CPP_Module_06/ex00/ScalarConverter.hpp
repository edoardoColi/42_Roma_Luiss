#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter
{
private:
	ScalarConverter();	
public:
	ScalarConverter(const ScalarConverter &scalarConverter); 
	~ScalarConverter();
	ScalarConverter &operator=(const ScalarConverter &scalarConverter);

	static void	convert(const std::string literal);
};

#endif