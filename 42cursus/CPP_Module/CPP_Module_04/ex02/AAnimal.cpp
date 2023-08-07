/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, const AAnimal &AAnimal)
{
	stream << \
	"In this Zoo I'm a " << AAnimal.getType();
	return (stream);
}

//Constructors
AAnimal::AAnimal()
{
	this->type="";
	std::cout << "Constructor called(AAnimal)" << std::endl;
}

AAnimal::AAnimal(const AAnimal &animal)
{
	*this = animal;
	return;
}

AAnimal	&AAnimal::operator = (const AAnimal &animal)
{
	this->type = animal.type;
	return (*this);
}

//Destructor
AAnimal::~AAnimal()
{
	std::cout << "Destructor called(AAnimal)" << std::endl;
}

//Setters

//Getters
std::string	AAnimal::getType() const
{
	return this->type;
}
