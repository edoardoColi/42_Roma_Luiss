/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp       	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

//Functions
void	FragTrap::highFivesGuys(void)
{
	std::cout << this->getName() << ": \"GIVE ME HIGH FIVES MATE!\"" << std::endl;
}

//Constructors
FragTrap::FragTrap()
: ClapTrap()
{
	this->hp = 100;
	this->mana = 100;
	this->ad = 30;
	std::cout << "Basic Constructor called(FragTrap)" << std::endl;
}

FragTrap::FragTrap(const std::string name)
: ClapTrap(name)
{
	this->hp = 100;
	this->mana = 100;
	this->ad = 30;
	std::cout << "Constructor called(FragTrap)" << std::endl;
}

FragTrap::FragTrap(const FragTrap &fragTrap)
{
	*this = fragTrap;
	return;
}

FragTrap	&FragTrap::operator = (const FragTrap &fragTrap)
{
	this->name = fragTrap.name;
	this->hp = fragTrap.hp;
	this->mana = fragTrap.mana;
	this->ad = fragTrap.ad;
	return (*this);
}

//Destructor
FragTrap::~FragTrap()
{
	std::cout << "Destructor called(FragTrap)" << std::endl;
}

//Setters

//Getters
