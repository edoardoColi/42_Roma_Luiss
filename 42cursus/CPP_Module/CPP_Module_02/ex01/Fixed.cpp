/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/*
*/
std::ostream	&operator << (std::ostream &stream, Fixed const &fix)
{
	stream << fix.toFloat();
	return (stream);
}

//Functions
/*
*/
float	Fixed::toFloat(void) const
{
	return ((float)this->number / (float)(1 << Fixed::bits));
}

/*
*/
int		Fixed::toInt(void) const
{
	return (this->number >> Fixed::bits);
}

//Constructors
Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->number = 0;
}

Fixed::Fixed(const Fixed &fix)
{
	std::cout << "Copy constructor called" << std::endl;
	this->number = fix.number;
}

Fixed::Fixed(const int integer)
{
	std::cout << "Int constructor called" << std::endl;
	this->number = (integer << Fixed::bits);
}

Fixed::Fixed(const float floating_point)
{
	std::cout << "Float constructor called" << std::endl;
	this->number = roundf(floating_point * (1 << Fixed::bits));
}

Fixed	&Fixed::operator = (const Fixed &fix)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->setRawBits(fix.getRawBits());	//Euivalent to: this->number = fix.number;
	return *this;
}

//Destructor
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

//Setters
void	Fixed::setRawBits(int const raw)
{
	this->number = raw;
}

//Getters
int	Fixed::getRawBits(void) const
{
	return number;
}
