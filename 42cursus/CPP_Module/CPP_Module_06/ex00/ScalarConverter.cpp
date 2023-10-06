/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

//Functions
/*
*/
void	ScalarConverter::convert(const std::string literal)
{
	std::string specialTypes[6] = {"-inff", "+inff", "nanf","-inf", "+inf", "nan"};
	std::string toChar = "";
	int toInt = 0;
	float toFloat = 0;
	double toDouble = 0;

	if (literal.size() == 1 && std::isprint(literal[0]) && !std::isdigit(literal[0])) 
	{
		toChar = literal[0];
		std::cout << "char: " << toChar << std::endl;
		std::cout << "int: " << static_cast<int>(toChar[0]) << std::endl;	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
		std::cout << "float: " << static_cast<float>(toChar[0]) << ".0f" << std::endl;	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
		std::cout << "double: " << static_cast<double>(toChar[0]) << ".0" << std::endl;	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
		return;
	}

	toInt = std::atoi(literal.c_str());

	if (literal[literal.length() - 1] == 'f') 
	{
		toFloat = std::atof(literal.c_str());
		toDouble = static_cast<double>(toFloat);	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
	} else 
	{
		toDouble = std::atof(literal.c_str());
		toFloat = static_cast<float>(toDouble);	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
	}

	for (int i = 0; i < 6; ++i) 
	{
		if (literal == specialTypes[i]) 
		{
			toChar = "impossible"; break;
		}
	}
	if (toChar == "" && std::isprint(toInt)) 
	{
		toChar = "'";
		toChar += static_cast<char>(toInt);	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
		toChar += "'";
	} 
	else if (toChar == "") 
	{
		toChar = "Non displayable";
	}

	std::cout << "char: " << toChar << std::endl;
	if (toChar == "impossible") 
	{
		std::cout << "int: impossible" << std::endl;
	} 
	else 
	{
		std::cout << "int: " << toInt << std::endl;
	}

	if (toChar == "impossible" && toFloat == 0) 
	{
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	} 
	else 
	{
		if (toChar != "impossible" && toFloat - static_cast<int>(toFloat) == 0)	//static cast is used for conversion that are wnown at compile time. It perform simple conversion between compatible types
		{
			std::cout << "float: " << toFloat << ".0f" << std::endl;
			std::cout << "double: " << toDouble << ".0" << std::endl;
		} 
		else 
		{
			std::cout << "float: " << toFloat << "f" << std::endl;
			std::cout << "double: " << toDouble << std::endl;
		}
	}

}

//Constructors
ScalarConverter::ScalarConverter()
{
	std::cout << "Constructor called(ScalarConverter)" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &scalarConverter)
{
	*this = scalarConverter;
}

ScalarConverter	&ScalarConverter::operator = (const ScalarConverter &ScalarConverter)
{
	return *this;
}

//Destructor
ScalarConverter::~ScalarConverter()
{
	std::cout << "Destructor called(ScalarConverter)" << std::endl;
}

//Setters

//Getters
