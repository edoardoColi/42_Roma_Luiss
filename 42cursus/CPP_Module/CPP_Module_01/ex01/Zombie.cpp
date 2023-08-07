/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

//Functions
/*
*/
void	Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

//Constructors
Zombie::Zombie()
{
}

Zombie::Zombie(const Zombie &zombie)
{
	*this = zombie;
	return;
}

Zombie	&Zombie::operator = (const Zombie &zombie)
{
	this->name = zombie.name;
	return (*this);
}

//Destructor
Zombie::~Zombie()
{
}

//Setters
void	Zombie::setName(std::string name)
{
	this->name = name;
}

//Getters
