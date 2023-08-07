/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp       	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

//Functions
/*
*/
void	ScavTrap::attack(const std::string& target)
{
	if (this->hp <= 0 || this->mana <= 0)
	{
		std::cout << "ScAvTrAp " << this->getName() << " cAn'T aTtAcK." << std::endl;
		return;
	}
	std::cout << "ScAvTrAp " << this->getName() << " aTtAcKs " << target << ", cAuSiNg " << this->getAd() << " pOiNtS oF dAmAgE!" << std::endl;
	this->mana = this->mana - 1;
}

/*
*/
void	ScavTrap::guardGate()
{
    std::cout  << "ScavTrap " << this->getName() << " has entered in Gate keeper mode." << std::endl;
}

//Constructors
ScavTrap::ScavTrap()
: ClapTrap()
{
	this->hp = 100;
	this->mana = 50;
	this->ad = 20;
	std::cout << "Basic Constructor called(ScavTrap)" << std::endl;
}

ScavTrap::ScavTrap(const std::string name)
: ClapTrap(name)
{
	this->hp = 100;
	this->mana = 50;
	this->ad = 20;
	std::cout << "Constructor called(ScavTrap)" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &scavTrap)
{
	*this = scavTrap;
	return;
}

ScavTrap	&ScavTrap::operator = (const ScavTrap &scavTrap)
{
	this->name = scavTrap.name;
	this->hp = scavTrap.hp;
	this->mana = scavTrap.mana;
	this->ad = scavTrap.ad;
	return (*this);
}

//Destructor
ScavTrap::~ScavTrap()
{
	std::cout << "Destructor called(ScavTrap)" << std::endl;
}

//Setters

//Getters
