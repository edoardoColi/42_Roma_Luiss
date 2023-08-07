/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:48:02 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

//Functions
/*
*/
void PhoneBook::usage()
{
	std::cout << std::endl;
	std::cout << "--------------USAGE---------------" << std::endl;
	std::cout << "ADD\t: To add a contact." << std::endl;
	std::cout << "SEARCH\t: To search for a contact." << std::endl;
	std::cout << "EXIT\t: to quite the PhoneBook." << std::endl;
	std::cout << "----------------------------------" << std::endl;
	std::cout << std::endl;
}

/*
*/
void PhoneBook::addContact(std::string fn, std::string lf, std::string nn, std::string pn, std::string sc)
{
	this->lastPos++;
	this->entry[this->lastPos % MAX_ENTRYS].setAll(fn, lf, nn, pn, sc);
	if (this->lastPos >= MAX_ENTRYS)
		this->firstPos++;
}

/*
*/
void PhoneBook::list()
{
	std::cout << "--------------PHONBOOK CONTACTS--------------" << std::endl;
	for (int i = 0; i < MAX_ENTRYS; i++){
		Contact tmp = this->entry[(this->firstPos + i) % MAX_ENTRYS];
		std::cout << "|" << std::setw(10) << std::left << i + 1;
		if (tmp.getFirstName().length() <= 10) 
			std::cout << "|" << std::setw(10) << std::left << tmp.getFirstName();
		else
			std::cout << "|" << tmp.getFirstName().substr(0, 9) << ".";
		if (tmp.getLastName().length() <= 10) 
			std::cout << "|" << std::setw(10) << std::left << tmp.getLastName();
		else
			std::cout << "|" << tmp.getLastName().substr(0, 9) << ".";
		if (tmp.getNickname().length() <= 10) 
			std::cout << "|" << std::setw(10) << std::left << tmp.getNickname();
		else
			std::cout << "|" << tmp.getNickname().substr(0, 9) << ".";
		std::cout << "|" << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;
}

/*
*/
int PhoneBook::printContact(int i)
{
	std::cout << i<<std::endl;
	if(i <= 0 || i > MAX_ENTRYS){
		return 1;
	}
	if (this->entry[(this->firstPos + (i - 1)) % MAX_ENTRYS].getFirstName().empty())
		std::cout << "> Empty slot" << std::endl;
	else
		this->entry[(this->firstPos + (i - 1)) % MAX_ENTRYS].fullDisplay();
	return 0;
}

//Constructors
PhoneBook::PhoneBook()
{
	this->lastPos = -1;
	this->firstPos = 0;
}

PhoneBook::PhoneBook(const PhoneBook &phoneBook)
{
	*this = phoneBook;
	return;
}

PhoneBook	&PhoneBook::operator = (const PhoneBook &phoneBook)
{
	for (int i=0; i<MAX_ENTRYS; i++)
	{
		this->entry[i] = phoneBook.entry[i];
	}
	this->lastPos = phoneBook.lastPos;
	this->firstPos = phoneBook.firstPos;
	return (*this);
}

//Destructor
PhoneBook::~PhoneBook()
{
}

//Setters

//Getters
