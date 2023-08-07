/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

//Functions
/*
*/
void	Cat::makeSound() const
{
	std::cout << "~ ~ ~ Miaoo! ~ ~ ~" << std::endl;
}

//Constructors
Cat::Cat()
{
	this->type = "Cat";
	std::cout << "Constructor called(Cat)" << std::endl;
}

Cat::Cat(const Cat &cat)
{
	*this = cat;
	return;
}

Cat	&Cat::operator = (const Cat &cat)
{
	this->type = cat.type;
	return (*this);
}

//Destructor
Cat::~Cat()
{
	std::cout << "Destructor called(Cat)" << std::endl;
}

//Setters

//Getters
