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
	std::cout << "Constructor called(Cat)" << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
}

Cat::Cat(const Cat &cat)
{
	this->brain = new Brain();	//perche e' indispensabile
	*this = cat;
	return;
}

Cat	&Cat::operator = (const Cat &cat)
{
	this->type = cat.type;
	// this->brain = cat.brain;	//TODO dovrebbe essere uguale a sotto
	(*this->brain) = (*cat.brain);
	return (*this);
}

//Destructor
Cat::~Cat()
{
	delete this->brain;
	std::cout << "Destructor called(Cat)" << std::endl;
}

//Setters

//Getters
Brain*	Cat::getBrain(void) const
{
	return this->brain;
}
