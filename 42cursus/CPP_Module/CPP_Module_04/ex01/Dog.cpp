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
	this->brain = new Brain();
}

Dog::Dog(const Dog &dog)
{
	this->brain = new Brain();	//perche e' indispensabile questa riga?
	*this = dog;
	return;
}

Dog	&Dog::operator = (const Dog &dog)
{
	this->type = dog.type;
	// this->brain = dog.brain;	//TODO dovrebbe essere uguale a sotto
	(*this->brain) = (*dog.brain);
	return (*this);
}

//Destructor
Dog::~Dog()
{
	delete this->brain;
	std::cout << "Destructor called(Dog)" << std::endl;
}

//Setters

//Getters
Brain*	Dog::getBrain(void) const
{
	return this->brain;
}