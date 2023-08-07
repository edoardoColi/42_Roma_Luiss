/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, const Animal &animal)
{
	stream << \
	"In this Zoo I'm a " << animal.getType();
	return (stream);
}

/*
*/
void	Animal::makeSound() const
{
	std::cout << "~ ~ ~ (Silence) ~ ~ ~" << std::endl;
}

//Constructors
Animal::Animal()
{
	this->type="";
	std::cout << "Constructor called(Animal)" << std::endl;
}

Animal::Animal(const Animal &animal)
{
	*this = animal;
	return;
}

Animal	&Animal::operator = (const Animal &animal)
{
	this->type = animal.type;
	return (*this);
}

//Destructor
Animal::~Animal()
{
	std::cout << "Destructor called(Animal)" << std::endl;
}

//Setters

//Getters
std::string	Animal::getType() const
{
	return this->type;
}
