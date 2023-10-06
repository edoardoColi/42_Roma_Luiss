/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, Bureaucrat &bureaucrat)
{
	stream << \
	bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return (stream);
}

/*
*/
void	Bureaucrat::incrementGrade()
{
	if (this->grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	else
		this->grade--;
}

/*
*/
void	Bureaucrat::decrementGrade()
{
	if (this->grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	else
		this->grade++;
}

//Constructors
Bureaucrat::Bureaucrat()
:name("")
{
	this->grade = 75;
	std::cout << "Constructor called(Bureaucrat)" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &bureaucrat)
:name(bureaucrat.name)
{
	this->grade = bureaucrat.grade;
}

Bureaucrat::Bureaucrat(std::string name, int grade)
:name(name)
{
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	if (grade < 1)
		throw  Bureaucrat::GradeTooHighException();
	this->grade = grade;
}

Bureaucrat	&Bureaucrat::operator = (const Bureaucrat &bureaucrat)
{
	this->~Bureaucrat();
	::new(this) Bureaucrat(bureaucrat);
	return (*this);
}

//Destructor
Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called(Bureaucrat)" << std::endl;
}

//Setters
void	Bureaucrat::setGrade(int const grade)
{
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	if (grade < 1)
		throw  Bureaucrat::GradeTooHighException();
	this->grade = grade;
}

//Getters
std::string	Bureaucrat::getName() const
{
	return this->name;
}

int	Bureaucrat::getGrade() const
{
	return this->grade;
}

//Exceptions
const char* Bureaucrat::GradeTooHighException::message = "Grade is going too high.";
const char * Bureaucrat::GradeTooHighException::what() const throw() 
{
	return this->message;
}

const char* Bureaucrat::GradeTooLowException::message = "Grade is going too low.";
const char * Bureaucrat::GradeTooLowException::what() const throw() 
{
	return this->message;
}
