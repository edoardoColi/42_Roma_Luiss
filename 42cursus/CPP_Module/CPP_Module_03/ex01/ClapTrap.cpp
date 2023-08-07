/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp       	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, ClapTrap &clapTrap)
{
	stream << \
	"Name: " << clapTrap.getName() << std::endl << \
	"  Hit Points: " << (clapTrap.getHp() > 0 ? clapTrap.getHp() : 0) << std::endl << \
	"  Energy Points: " << clapTrap.getMana() << std::endl << \
	"  Attack Damage: " << clapTrap.getAd() << std::endl;
	return (stream);
}

/*
*/
void	ClapTrap::attack(const std::string& target)
{
	if (this->hp <= 0 || this->mana <= 0)
	{
		std::cout << "ClapTrap " << this->name << " can't attack." << std::endl;
		return;
	}
	std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " << this->ad << " points of damage!" << std::endl;
	this->mana--;
}

/*
*/
void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << this->name << " loses -" << amount << " healt point(s)." << std::endl;
	this->hp -= amount;
}

/*
*/
void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->hp <= 0 || this->mana <= 0)
	{
		std::cout << "ClapTrap " << this->name << " can't recover Hp." << std::endl;
		return;
	}
	std::cout << "ClapTrap " << this->name << " repairs +" << amount << " healt point(s)." << std::endl;
	this->mana--;
	this->hp += amount;
}

//Constructors
ClapTrap::ClapTrap()
{
	this->name = "";
	this->hp = 10;
	this->mana = 10;
	this->ad = 0;
	std::cout << "Basic Constructor called(ClapTrap)" << std::endl;
}

ClapTrap::ClapTrap(const std::string name)
{
	this->name = name;
	this->hp = 10;
	this->mana = 10;
	this->ad = 0;
	std::cout << "Constructor called(ClapTrap)" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &clapTrap)
{
	*this = clapTrap;
	return;
}

ClapTrap	&ClapTrap::operator = (const ClapTrap &clapTrap)
{
	this->name = clapTrap.name;
	this->hp = clapTrap.hp;
	this->mana = clapTrap.mana;
	this->ad = clapTrap.ad;
	return (*this);
}

//Destructor
ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called(ClapTrap)" << std::endl;
}

//Setters

//Getters
std::string	ClapTrap::getName() const
{
	return this->name;
}

int	ClapTrap::getHp() const
{
	return this->hp;
}

int	ClapTrap::getMana() const
{
	return this->mana;
}

int	ClapTrap::getAd() const
{
	return this->ad;
}
