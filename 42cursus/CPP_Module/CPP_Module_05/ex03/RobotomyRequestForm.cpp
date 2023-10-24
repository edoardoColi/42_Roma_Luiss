/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

//Functions
/*
*/
// std::ostream	&operator << (std::ostream &stream, RobotomyRequestForm &form)
// {
// 	stream << \
// 	form.getName() << "=> form grade to sign: " << form.getSignGrade() << ", form grade to exec: " <<  form.getExecGrade() << ".";
// 	return (stream);
// }

/*
*/
void RobotomyRequestForm::execute(Bureaucrat const &executor) const 
{
	if (this->isSigned() && executor.getGrade() <= this->getExecGrade())
	{
		std::cout << "...DRILLLLL..." << std::endl;
		srand((long) this);//serve davvero?
		if (rand() % 2 == 0) 
			std::cout << this->target << " has been robotomized successfully." << std::endl;
		else 
			std::cout << this->target << " robotomy failed." << std::endl;
	}
	else
		throw AForm::ExecutionException();
}

AForm* RobotomyRequestForm::clone(std::string target)
{
	return new RobotomyRequestForm(target);
}

//Constructors
RobotomyRequestForm::RobotomyRequestForm()
:AForm("RobotomyRequestForm", 72, 45)
{
	this->target = "";
	std::cout << "Constructor called(RobotomyRequestForm)" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &rrf)
:AForm(rrf.getName(), rrf.getSignGrade(), rrf.getExecGrade())
{
	this->target = rrf.target;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target)
:AForm("RobotomyRequestForm", 72, 45)
{
	this->target = target;
}

RobotomyRequestForm	&RobotomyRequestForm::operator = (const RobotomyRequestForm &rrf)
{
	this->~RobotomyRequestForm();
	::new(this) RobotomyRequestForm(rrf);
	return (*this);
}

//Destructor
RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Destructor called(RobotomyRequestForm)" << std::endl;
}

//Setters

//Getters
