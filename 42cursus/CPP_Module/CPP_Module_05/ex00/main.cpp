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

/*
*/
int main(void)
{
	try
	{
		Bureaucrat bureaucrat("bob", 200);
		std::cout << bureaucrat << std::endl;
	}
	catch (Bureaucrat::GradeTooHighException &e) 
	{
		std::cerr << "Catch the TooHighException" << std::endl;
	}
	catch (Bureaucrat::GradeTooLowException &e) 
	{
		std::cerr << "Catch the TooLowException" << std::endl;
	}

	try
	{
		Bureaucrat bureaucrat("bob", 2);
		std::cout << bureaucrat << std::endl;
	}
	catch (Bureaucrat::GradeTooHighException &e) 
	{
		std::cerr << "Catch the TooHighException" << std::endl;
	}
	catch (Bureaucrat::GradeTooLowException &e) 
	{
		std::cerr << "Catch the TooLowException" << std::endl;
	}

	try
	{
		Bureaucrat bureaucrat1("bob", 1);
		bureaucrat1.incrementGrade();
		std::cout << bureaucrat1 << std::endl;
	}
	catch (Bureaucrat::GradeTooHighException &e) 
	{
		std::cerr << "Catch the TooHighException" << std::endl;
	}
	catch (Bureaucrat::GradeTooLowException &e) 
	{
		std::cerr << "Catch the TooLowException" << std::endl;
	}

	try
	{
		Bureaucrat bureaucrat2("bob", 149);
		bureaucrat2.decrementGrade();
		std::cout << bureaucrat2 << std::endl;
	}
	catch (Bureaucrat::GradeTooHighException &e) 
	{
		std::cerr << "Catch the TooHighException: " << e.what() << std::endl;
	}
	catch (Bureaucrat::GradeTooLowException &e) 
	{
		std::cerr << "Catch the TooLowException: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat bureaucrat2("bob", 150);
		bureaucrat2.decrementGrade();
		std::cout << bureaucrat2 << std::endl;
	}
	catch (Bureaucrat::GradeTooHighException &e) 
	{
		std::cerr << "Catch the TooHighException: " << e.what() << std::endl;
	}
	catch (Bureaucrat::GradeTooLowException &e) 
	{
		std::cerr << "Catch the TooLowException: " << e.what() << std::endl;
	}
	return (0);
}