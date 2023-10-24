/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

//Functions
/*
*/
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const 
{
	if (this->isSigned() && executor.getGrade() <= this->getExecGrade())
	{
		std::ofstream outFile(this->target + "_shrubbery");
		if (!outFile) 
		{
			std::cerr << "can't open/create " << this->target + "_shrubbery" << std::endl;
			return ;
		}
		outFile << 
		"            # #### ####\n"
		"        ### \\/#|### |/####\n"
		"        ##\\/#/ \\||/##/_/##/_#\n"
		"       ###  \\/###|/ \\/ oEo##\n"
		"    ##_\\_#\\_\\## | #/##ooo_####\n"
		"    ## #### # \\ #| /  ### ##/##\n"
		"    __#_--###`  |{,###---###-~\n"
		"                \\ }{\n"
		"                }}{\n"
		"                }}{\n"
		"                {{}\n"
		"        , -=-~{ .-^- _}!=-#"
		<< std::endl;
	}
	else
		throw AForm::ExecutionException();
}

//Constructors
ShrubberyCreationForm::ShrubberyCreationForm()
:AForm("ShrubberyCreationForm", 145, 137)
{
	this->target = "";
	std::cout << "Constructor called(ShrubberyCreationForm)" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &scf)
:AForm(scf.getName(), scf.getSignGrade(), scf.getExecGrade())
{
	this->target = scf.target;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
:AForm("ShrubberyCreationForm", 145, 137)
{
	this->target = target;
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator = (const ShrubberyCreationForm &scf)
{
	this->~ShrubberyCreationForm();
	::new(this) ShrubberyCreationForm(scf);
	return (*this);
}

//Destructor
ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "Destructor called(ShrubberyCreationForm)" << std::endl;
}

//Setters

//Getters
