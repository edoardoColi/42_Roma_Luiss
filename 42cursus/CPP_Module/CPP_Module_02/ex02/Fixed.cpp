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

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, Fixed const &fix)
{
	stream << fix.toFloat();
	return (stream);
}

/*
*/
Fixed	&Fixed::operator = (const Fixed &fix)
{
	// cout << "Copy assignment operator called" << endl;
	this->number = fix.number;
	return *this;
}

/*
*/
Fixed	Fixed::operator + (Fixed const &fix)
{
	Fixed tmp;
	tmp.setRawBits(this->number + fix.getRawBits());
	return tmp;
}

/*
*/
Fixed	Fixed::operator - (Fixed const &fix)
{
	Fixed tmp;
	tmp.setRawBits(this->number - fix.getRawBits());
	return tmp;
}

/*
*/
Fixed	Fixed::operator * (Fixed const &fix)
{
	Fixed tmp;
	tmp.setRawBits((this->toFloat() * fix.toFloat()) * (1 << bits));
	return tmp;
}

/*
*/
Fixed	Fixed::operator / (Fixed const &fix)
{
	Fixed tmp;
	tmp.setRawBits((this->toFloat() / fix.toFloat()) * (1 << bits));
	return tmp;
}

/*
*/
bool	Fixed::operator > (Fixed const &fix) const
{
	if (this->number > fix.getRawBits())
		return true;
	return false;
}

/*
*/
bool	Fixed::operator < (Fixed const &fix) const
{
	if (this->number < fix.getRawBits())
		return true;
	return false;
}

/*
*/
bool	Fixed::operator >= (Fixed const &fix) const
{
	if (this->number >= fix.getRawBits())
		return true;
	return false;
}

/*
*/
bool	Fixed::operator <= (Fixed const &fix) const
{
	if (this->number <= fix.getRawBits())
		return true;
	return false;
}

/*
*/
bool	Fixed::operator == (Fixed const &fix) const
{
	if (this->number == fix.getRawBits())
		return true;
	return false;
}

/*
*/
bool	Fixed::operator != (Fixed const &fix) const
{
	if (this->number != fix.getRawBits())
		return true;
	return false;
}

/*
*/
Fixed	Fixed::operator ++ ()
{
	this->number++;
	return *this;
}

/*
*/
Fixed	Fixed::operator ++ (int)
{
	Fixed	tmp(*this);
	++(*this);
	return tmp;
}

/*
*/
Fixed	Fixed::operator -- ()
{
	this->number--;
	return *this;
}

/*
*/
Fixed	Fixed::operator -- (int)
{
	Fixed	tmp(*this);
	--(*this);
	return tmp;
}

/*
*/
Fixed const	&Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

/*
*/
Fixed const	&Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a.getRawBits() < b.getRawBits())
		return b;
	return a;
}

/*
*/
Fixed	&Fixed::min(Fixed &a, Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

/*
*/
Fixed	&Fixed::max(Fixed &a, Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return b;
	return a;
}

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
	this->number = 0;
	// cout << "Default constructor called" << endl;
}

Fixed::Fixed(const Fixed &fix)
{
	// cout << "Copy constructor called" << endl;
	this->number = fix.number;
}

Fixed::Fixed(const int integer)
{
	// cout << "Int constructor called" << endl;
	this->number = (integer << Fixed::bits);
}

Fixed::Fixed(const float floating_point)
{
	// cout << "Float constructor called" << endl;
	this->number = roundf(floating_point * (1 << Fixed::bits));
}

//Destructor
Fixed::~Fixed()
{
	// cout << "Destructor called" << endl;
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
