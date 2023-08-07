/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

//Functions
/*
*/
void	WrongCat::makeSound() const
{
	std::cout << "~ ~ ~ Mara-Miaoo! ~ ~ ~" << std::endl;
}

//Constructors
WrongCat::WrongCat()
{
	this->type = "WrongCat";
	std::cout << "Constructor called(WrongCat)" << std::endl;
}

WrongCat::WrongCat(const WrongCat &wrongCat)
{
	*this = wrongCat;
	return;
}

WrongCat	&WrongCat::operator = (const WrongCat &wrongCat)
{
	this->type = wrongCat.getType();
	return (*this);
}

//Destructor
WrongCat::~WrongCat()
{
	std::cout << "Destructor called(WrongCat)" << std::endl;
}

//Setters

//Getters
