/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, AForm &form)
{
	stream << \
	form.getName() << "=> form grade to sign: " << form.getSignGrade() << ", form grade to exec: " <<  form.getExecGrade() << ".";
	return (stream);
}

/*
*/
int	validate(int grade)
{
	if (grade > 150)
		throw Bureaucrat::GradeTooHighException();
	if (grade < 1)
		throw  Bureaucrat::GradeTooLowException();
	return grade;
}

/*
*/
void	AForm::beSigned(Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= this->gradeLevelToSign)
		this->signedForm = true;
}

//Constructors
AForm::AForm()
:name(""),gradeLevelToSign(76),gradeLevelToExecution(76)
{
	this->signedForm = false;
	std::cout << "Constructor called(AForm)" << std::endl;
}

AForm::AForm(const AForm &form)
:name(form.name),gradeLevelToSign(form.gradeLevelToSign),gradeLevelToExecution(form.gradeLevelToExecution)
{
	this->signedForm = form.signedForm;
}

AForm::AForm(std::string name, int signGrade, int execGrade)
:name(name),gradeLevelToSign(validate(signGrade)),gradeLevelToExecution(validate(execGrade))
{
	this->signedForm = false;
}

AForm	&AForm::operator = (const AForm &form)
{
	//No sense function, here just for the Ortodox Form Constrain
	// this->~AForm();
	// ::new(this) AForm(form);
	return (*this);
}

//Destructor
AForm::~AForm()
{
	std::cout << "Destructor called(AForm)" << std::endl;
}

//Setters

//Getters
std::string	AForm::getName() const
{
	return this->name;
}

int	AForm::isSigned() const
{
	return this->signedForm;
}

int	AForm::getSignGrade() const
{
	return this->gradeLevelToSign;
}

int	AForm::getExecGrade() const
{
	return this->gradeLevelToExecution;
}

//Exceptions
const char* AForm::GradeTooHighException::message = "Grade for the form too high, will not be satisfiable.";
const char * AForm::GradeTooHighException::what() const throw() 
{
	return this->message;
}

const char* AForm::GradeTooLowException::message = "Grade for the form too low.";
const char * AForm::GradeTooLowException::what() const throw() 
{
	return this->message;
}

const char* AForm::ExecutionException::message = "Conditions to execute not satisfied.";
const char * AForm::ExecutionException::what() const throw() 
{
	return this->message;
}
