#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "AForm.hpp"
#include "Bureaucrat.hpp"
class Bureaucrat;	//Forward declaration for circular dependencies between header files

class ShrubberyCreationForm : public AForm 
{
private:
		std::string	target;
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string target);
	ShrubberyCreationForm(const ShrubberyCreationForm &scf);
	~ShrubberyCreationForm();
	ShrubberyCreationForm & operator = (const ShrubberyCreationForm &scf);

	void execute(Bureaucrat const &executor) const;
	AForm*	clone(std::string target);
};

#endif