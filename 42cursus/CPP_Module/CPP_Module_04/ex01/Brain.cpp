/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, const Brain &brain)
{
	int	bound = 5;
	stream << "My Brain with 'TODO' list:";
	for (int i = 0; i < bound; i++)
		stream << std::endl << "   " << i << ": \"" << brain.getIdea(i) << "\"";
	return (stream);
}

//Constructors
Brain::Brain()
{
	std::cout << "Constructor called(Brain)" << std::endl;
}

//Destructor
Brain::~Brain()
{
	std::cout << "Destructor called(Brain)" << std::endl;
}

Brain::Brain(const Brain &brain)
{
	*this = brain;
	return;
}

Brain	&Brain::operator = (const Brain &brain)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = brain.ideas[i];
	return (*this);
}

//Setters
void	Brain::setIdea(std::string idea, int n)
{
	this->ideas[n]=idea;
}

//Getters
std::string	Brain::getIdea(int n) const
{
	return this->ideas[n];
}
