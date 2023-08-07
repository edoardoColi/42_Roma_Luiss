/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

//Functions
/*
*/
void	Dog::makeSound() const
{
	std::cout << "~ ~ ~ Bau! ~ ~ ~" << std::endl;
}

//Constructors
Dog::Dog()
{
	this->type = "Dog";
	std::cout << "Constructor called(Dog)" << std::endl;
}

Dog::Dog(const Dog &dog)
{
	*this = dog;
	return;
}

Dog	&Dog::operator = (const Dog &dog)
{
	this->type = dog.type;
	return (*this);
}

//Destructor
Dog::~Dog()
{
	std::cout << "Destructor called(Dog)" << std::endl;
}

//Setters

//Getters
