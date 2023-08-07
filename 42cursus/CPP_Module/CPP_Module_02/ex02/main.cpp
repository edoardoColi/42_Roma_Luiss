/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 18:51:06 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

#include <iostream>

/*
*/
int main(void)
{
	Fixed	a;
	Fixed const	b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	
	std::cout << std::endl << "More tests:" << std::endl;
	std::cout << "Print a: " << a << std::endl;
	std::cout << "Print b: " << b << std::endl;
	std::cout << "Print a > b? " << (a > b) << " <- Expected " << false << std::endl;
	std::cout << "Print a < b? " << (a < b) << " <- Expected " << true << std::endl;
	std::cout << "Print a >= b? " << (a >= b) << " <- Expected " << false << std::endl;
	std::cout << "Print a <= b? " << (a <= b) << " <- Expected " << true << std::endl;
	std::cout << "Print a == b? " << (a == b) << " <- Expected " << false << std::endl;
	std::cout << "Print a != b? " << (a != b) << " <- Expected " << true << std::endl;
	std::cout << "Print a + b = " << (a + b) << std::endl;
	std::cout << "Print a - b = " << (a - b) << std::endl;
	std::cout << "Print a * b = " << (a * b) << std::endl;
	std::cout << "Print a / b = " << (a / b) << std::endl;
	std::cout << "Print a: " << a << std::endl;
	std::cout << "Print ++a = " << ++a << std::endl;
	std::cout << "Print a: " << a << std::endl;
	std::cout << "Print a++ = " << a++ << std::endl;
	std::cout << "Print a: " << a << std::endl;
	std::cout << "Print --a = " << --a << std::endl;
	std::cout << "Print a: " << a << std::endl;
	std::cout << "Print a-- = " << a-- << std::endl;
	std::cout << "Print a: " << a << std::endl;

	return 0;
}