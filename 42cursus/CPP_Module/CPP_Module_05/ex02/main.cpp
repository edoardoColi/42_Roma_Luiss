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

/*
*/
int main(void)
{
	AForm *SCF = new ShrubberyCreationForm("home");
	try 
	{
		Bureaucrat b1("Bob", 136);
		Bureaucrat b2("Jhon", 145);
		b2.signForm(*SCF);
		b1.executeForm(*SCF);
		b2.executeForm(*SCF);
		delete SCF;
	}
	
	catch (std::exception & e) {
		std::cout << "Exception catched: " << e.what() << std::endl;
		delete SCF;
	}

	std::cout  << "<<<<<<<<<<<<>>>>>>>>>>>" << std::endl;

	AForm *RRF = new RobotomyRequestForm("carl");
	try 
	{
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
		delete RRF;
	}

	std::cout  << "<<<<<<<<<<<<>>>>>>>>>>>" << std::endl;

		AForm *PPF = new PresidentialPardonForm("nixon");
	try 
	{
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
		delete PPF;
	}
	return (0);
}