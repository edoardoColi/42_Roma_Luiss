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
#include "Form.hpp"

/*
*/
int main(void)
{
	try 
	{
		Form form1("Player Contract", 150, 150);
		Bureaucrat bCrat1("Richarlison", 1);
		bCrat1.signForm(form1);
		std::cout << "Welcome to the Club" << std::endl;
		bCrat1.incrementGrade(); 
	}
	catch (std::exception &e) 
	{
		std::cout << "About to print the exception" << std::endl;
		std::cout << e.what() << std::endl;
	}

	std::cout  << "<<<<<<<<<<<<>>>>>>>>>>>" << std::endl;
	try 
	{
		Form form1("Drivers License", 1, 1);
		std::cout << form1 << std::endl;
		Bureaucrat bCrat1("Caitlyn Jenner", 150);
		bCrat1.signForm(form1);
	}
	catch (std::exception &e) 
	{
		std::cout << "About to print the exception" << std::endl;
		std::cout << e.what() << std::endl;
	}

	std::cout << "<<<<<<<<<<<<<>>>>>>>>>>>>>" << std::endl;
	Form form1;
	Form pContract("PlayerContract", 1, 1);
	Form pApplication("Passport Application", 150, 150);
	Form copyApplication(pApplication);
	
	std::cout << form1 << std::endl;
	form1 = pContract;
	std::cout << "Uknown Form should become a Player Contract now" << std::endl;
	std::cout << form1 << std::endl;
	std::cout << "<<<<<<<<<<<<<>>>>>>>>>>>>>" << std::endl;
	std::cout << copyApplication << std::endl;
	return (0);
}