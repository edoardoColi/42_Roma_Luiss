/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 18:51:06 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

/*
*/
int main(void)
{
	Intern intern;

	AForm *SCF = NULL;
	try
	{
		SCF = intern.makeForm("ShrubberyCreationForm", "home");
		Bureaucrat b1("Bob", 136);
		Bureaucrat b2("Jhon", 145);
		b2.signForm(*SCF);
		b1.executeForm(*SCF);

		b2.executeForm(*SCF);
		delete SCF;
	}
	
	catch (std::exception & e) 
	{
		std::cout << "Exception: " << e.what() << std::endl;
		if (SCF)
			delete SCF;
	}

	AForm *RRF = NULL;
	try
	{
		RRF = intern.makeForm("RobotomyRequestForm", "home");
		Bureaucrat b1("Bob2", 44);
		Bureaucrat b2("Jhon2", 72);
		b2.signForm(*RRF);
		b1.executeForm(*RRF);

		b2.executeForm(*RRF);
		delete RRF;
	}

	catch (std::exception & e) 
	{
		std::cout << "Exception: " << e.what() << std::endl;
		if (RRF)
			delete RRF;
	}

	AForm *PPF = NULL;
	try
	{
		PPF = intern.makeForm("PresidentialPardonForm", "home");
		std::cout << *PPF << std::endl;
		Bureaucrat b1("Bob3", 5);
		Bureaucrat b2("Jhon3", 24);
		b2.signForm(*PPF);
		b1.executeForm(*PPF);

		b2.executeForm(*PPF);
		delete PPF;
	}

	catch (std::exception & e) 
	{
		std::cout << "Exception: " << e.what() << std::endl;
		if (PPF)
			delete PPF;
	}

	AForm *NEF = NULL;
	try
	{
		NEF = intern.makeForm("NoneExistingForm", "home");
		std::cout << *NEF << std::endl;
		Bureaucrat b1("Bob4", 5);
		Bureaucrat b2("Jhon4", 24);
		b2.signForm(*NEF);
		b1.executeForm(*NEF);

		b2.executeForm(*NEF);
		delete NEF;
	}

	catch (std::exception & e) 
	{
		std::cout << "Exception: " << e.what() << std::endl;
		if (NEF)
			delete NEF;
	}
	return (0);
}