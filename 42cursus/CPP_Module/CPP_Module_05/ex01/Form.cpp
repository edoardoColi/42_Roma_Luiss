/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, Form &form)
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
void	Form::beSigned(Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= this->gradeLevelToSign)
		this->signedForm = true;
}

//Constructors
Form::Form()
:name(""),gradeLevelToSign(76),gradeLevelToExecution(76)
{
	this->signedForm = false;
	std::cout << "Constructor called(Form)" << std::endl;
}

Form::Form(const Form &form)
:name(form.name),gradeLevelToSign(form.gradeLevelToSign),gradeLevelToExecution(form.gradeLevelToExecution)
{
	this->signedForm = form.signedForm;
}

Form::Form(std::string name, int signGrade, int execGrade)
:name(name),gradeLevelToSign(validate(signGrade)),gradeLevelToExecution(validate(execGrade))
{
	this->signedForm = false;
}

Form	&Form::operator = (const Form &form)
{
	this->~Form();
	::new(this) Form(form);
	return (*this);
}

//Destructor
Form::~Form()
{
	std::cout << "Destructor called(Form)" << std::endl;
}

//Setters

//Getters
std::string	Form::getName() const
{
	return this->name;
}

int	Form::isSigned() const
{
	return this->signedForm;
}

int	Form::getSignGrade() const
{
	return this->gradeLevelToSign;
}

int	Form::getExecGrade() const
{
	return this->gradeLevelToExecution;
}

//Exceptions
const char* Form::GradeTooHighException::message = "Grade for the form too high, will not be satisfiable.";
const char * Form::GradeTooHighException::what() const throw() 
{
	return this->message;
}

const char* Form::GradeTooLowException::message = "Grade for the form too low.";
const char * Form::GradeTooLowException::what() const throw() 
{
	return this->message;
}
