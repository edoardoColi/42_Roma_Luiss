/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

//Functions

//Constructors
Weapon::Weapon(std::string type)
{
	this->type = type;
}

Weapon::Weapon(const Weapon &weapon)
{
	*this = weapon;
	return;
}

Weapon	&Weapon::operator = (const Weapon &weapon)
{
	this->type = weapon.type;
	return (*this);
}

//Destructor
Weapon::~Weapon()
{
}

//Setters
void	Weapon::setType(std::string type)
{
	this->type = type;
}

//Getters
const std::string&	Weapon::getType() const
{
	return this->type;
}