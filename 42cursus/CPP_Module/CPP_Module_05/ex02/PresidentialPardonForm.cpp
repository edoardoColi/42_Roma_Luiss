/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

//Functions
/*
*/
void PresidentialPardonForm::execute(Bureaucrat const &executor) const 
{
	if (this->isSigned() && executor.getGrade() <= this->getExecGrade())
	    std::cout << this->target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
	else
		throw AForm::ExecutionException();
}

//Constructors
PresidentialPardonForm::PresidentialPardonForm()
:AForm("PresidentialPardonForm", 25, 5)
{
	this->target = "";
	std::cout << "Constructor called(PresidentialPardonForm)" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &scf)
:AForm(scf.getName(), scf.getSignGrade(), scf.getExecGrade())
{
	this->target = scf.target;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target)
:AForm("PresidentialPardonForm", 25, 5)
{
	this->target = target;
}

PresidentialPardonForm	&PresidentialPardonForm::operator = (const PresidentialPardonForm &scf)
{
	this->~PresidentialPardonForm();
	::new(this) PresidentialPardonForm(scf);
	return (*this);
}

//Destructor
PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "Destructor called(PresidentialPardonForm)" << std::endl;
}

//Setters

//Getters
