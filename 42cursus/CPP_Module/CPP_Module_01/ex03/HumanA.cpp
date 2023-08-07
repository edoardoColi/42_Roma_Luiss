/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

//Functions
/*
*/
void    HumanA::attack()
{
	if (!this->weapon.getType().empty())
		std::cout << name << " attacks with their " << this->weapon.getType() << std::endl;
	else
		std::cout << name << " doesn't have a weapon to attack." << std::endl;
}

//Constructors
HumanA::HumanA(std::string name, Weapon &weapon)
:weapon(weapon)// Using the initializer list to initialize the reference member variable, we guarantee that the reference is properly initialized with a valid object.
{
	this->name = name;
}

HumanA::HumanA(const HumanA &humanA)
: weapon(weapon)// Using the initializer list to initialize the reference member variable, we guarantee that the reference is properly initialized with a valid object.
{
	*this = humanA;
	return;
}

HumanA	&HumanA::operator = (const HumanA &humanA)
{
	this->name = humanA.name;
	this->weapon = humanA.weapon;
	return (*this);
}

//Destructor
HumanA::~HumanA()
{
}

//Setters

//Getters
