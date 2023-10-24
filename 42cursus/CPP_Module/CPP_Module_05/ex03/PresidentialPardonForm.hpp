#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "AForm.hpp"
#include "Bureaucrat.hpp"
class Bureaucrat;	//Forward declaration for circular dependencies between header files

class PresidentialPardonForm : public AForm 
{
private:
		std::string	target;
public:
	PresidentialPardonForm();
	PresidentialPardonForm(std::string target);
	PresidentialPardonForm(const PresidentialPardonForm &scf);
	~PresidentialPardonForm();
	PresidentialPardonForm & operator = (const PresidentialPardonForm &scf);

	void execute(Bureaucrat const &executor) const;
	AForm*	clone(std::string target);
};

#endif