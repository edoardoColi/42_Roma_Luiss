/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

//Functions
/*
*/
void    HumanB::attack()
{
	if (this->weapon && !this->weapon->getType().empty())
		std::cout << name << " attacks with their " << this->weapon->getType() << std::endl;
	else
		std::cout << name << " doesn't have a weapon to attack." << std::endl;
}

//Constructors
HumanB::HumanB(std::string name)
{
	this->name = name;
	this->weapon = NULL;
}

HumanB::HumanB(const HumanB &humanB)
{
	*this = humanB;
	return;
}

HumanB	&HumanB::operator = (const HumanB &humanB)
{
	this->name = humanB.name;
	this->weapon = humanB.weapon;
	return (*this);
}

//Destructor
HumanB::~HumanB()
{
}

//Setters
void	HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}

//Getters
