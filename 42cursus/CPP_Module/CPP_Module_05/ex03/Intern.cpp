/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

//Functions
/*
*/
AForm*	Intern::makeForm(std::string nameForm, std::string target)
{
	AForm* form = NULL;
	switch (nameForm[0]) {
		case 'P':
			form = forms[2]->clone(target);
			break;
		case 'R':
			form = forms[1]->clone(target);
			break;
		case 'S':
			form = forms[0]->clone(target);
			break;
		default:
			throw Intern::NotAvailableForm();
			break;
	}
	std::cout << "Intern creates " << target << std::endl;
	return form;
}

//Constructors
Intern::Intern()
{
	this->forms[0] = new ShrubberyCreationForm();
	this->forms[1] = new RobotomyRequestForm();
	this->forms[2] = new PresidentialPardonForm();
	std::cout << "Constructor called(Intern)" << std::endl;
}

Intern::Intern(const Intern &form)
{
	this->forms[0] = new ShrubberyCreationForm();
	this->forms[1] = new RobotomyRequestForm();
	this->forms[2] = new PresidentialPardonForm();
	return;
}

Intern	&Intern::operator = (const Intern &form)
{
	return (*this);
}

//Destructor
Intern::~Intern()
{
	delete forms[0];
	delete forms[1];
	delete forms[2];
	std::cout << "Destructor called(Intern)" << std::endl;
}

//Setters

//Getters

//Exceptions
const char* Intern::NotAvailableForm::message = "Unknown form name.";
const char * Intern::NotAvailableForm::what() const throw() 
{
	return this->message;
}
