/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, WrongAnimal &wrongAnimal)
{
	stream << \
	"In this WrongZoo I'm a " << wrongAnimal.getType() << std::endl;
	return (stream);
}

/*
*/
void	WrongAnimal::makeSound() const
{
	std::cout << "~ ~ ~ (Wrong Silence) ~ ~ ~" << std::endl;
}

//Constructors
WrongAnimal::WrongAnimal()
{
	std::cout << "Constructor called(WrongAnimal)" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &wrongAnimal)
{
	*this = wrongAnimal;
	return;
}

WrongAnimal	&WrongAnimal::operator = (const WrongAnimal &wrongAnimal)
{
	this->type = wrongAnimal.type;
	return (*this);
}

//Destructor
WrongAnimal::~WrongAnimal()
{
	std::cout << "Destructor called(WrongAnimal)" << std::endl;
}

//Setters

//Getters
std::string	WrongAnimal::getType() const
{
	return this->type;
}
