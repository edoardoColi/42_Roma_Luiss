/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

//Functions
void	Harl::debug(void) 
{
	std::cout << "[DEBUG]" << std::endl << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger. I really do!" << std::endl;
}

void	Harl::info(void) 
{
	std::cout << "[INFO]" << std::endl << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
}

void	Harl::warning(void) 
{
	std::cout << "[WARNING]" << std::endl << "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month." << std::endl;
}

void	Harl::error(void) 
{
	std::cout << "[ERROR]" << std::endl << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void	Harl::complain(std::string level)
{
	int lvl = -1;

	switch (level[0]) {
		case 'D':
			lvl = 0;
			break;
		case 'I':
			lvl = 1;
			break;
		case 'W':
			lvl = 2;
			break;
		case 'E':
			lvl = 3;
			break;
		default:
			std::cout << "No match" << std::endl;
			break;
	}
	(this->*complains[lvl])();
}

//Constructors
Harl::Harl()
{
	this->complains[0]= &Harl::debug;
	this->complains[1]= &Harl::info;
	this->complains[2]= &Harl::warning;
	this->complains[3]= &Harl::error;
}

Harl::Harl(const Harl &harl)
{
	*this = harl;
	return;
}

Harl	&Harl::operator = (const Harl &harl)	//Not very useful because all HARL objects already have these functions defined in the constructor
{
	this->complains[0] = harl.complains[0];
	this->complains[1] = harl.complains[1];
	this->complains[2] = harl.complains[2];
	this->complains[3] = harl.complains[3];
	return (*this);
}

//Destructor
Harl::~Harl()
{
}

//Setters

//Getters
