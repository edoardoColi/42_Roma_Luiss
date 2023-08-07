/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

//Functions
/*
*/
void Contact::fullDisplay()
{
	std::cout << "First name: " << this->first_name << std::endl;
	std::cout << "Last name: " << this->last_name << std::endl;
	std::cout << "Nickname: " << this->nickname << std::endl;
	std::cout << "Phone number: " << this->phone_number << std::endl;
	std::cout << "Secret: " << this->secret << std::endl;
}

//Constructors
Contact::Contact()
{
}

Contact::Contact(const Contact &contact)
{
	*this = contact;
	return;
}

Contact	&Contact::operator = (const Contact &contact)
{
	this->first_name = contact.first_name;
	this->last_name = contact.last_name;
	this->nickname = contact.nickname;
	this->phone_number = contact.phone_number;
	this->secret = contact.secret;
	return (*this);
}

//Destructor
Contact::~Contact()
{
}

//Setters
/*
*/
void Contact::setAll(std::string fn, std::string lf, std::string nn, std::string pn, std::string sc)
{
	this->first_name = fn;
	this->last_name = lf;
	this->nickname = nn;
	this->phone_number = pn;
	this->secret = sc;
}

//Getters
std::string Contact::getFirstName() const
{
	return this->first_name;
}

std::string Contact::getLastName() const
{
	return this->last_name;
}

std::string Contact::getNickname() const
{
	return this->nickname;
}

std::string Contact::getPhoneNumber() const
{
	return this->phone_number;
}

std::string Contact::getSecret() const
{
	return this->secret;
}
