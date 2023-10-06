#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "AForm.hpp"
#include "Bureaucrat.hpp"
class Bureaucrat;	//Forward declaration for circular dependencies between header files

class RobotomyRequestForm : public AForm 
{
private:
		std::string	target;
public:
	RobotomyRequestForm();
	RobotomyRequestForm(std::string target);
	RobotomyRequestForm(const RobotomyRequestForm &rrf);
	~RobotomyRequestForm();
	RobotomyRequestForm & operator = (const RobotomyRequestForm &rrf);

	void execute(Bureaucrat const &executor) const;
};

#endif