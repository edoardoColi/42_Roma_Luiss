#ifndef INTERN_HPP
# define INTERN_HPP

#include <exception>
#include <iostream>
#include <string>

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
private:
	AForm *forms[3];

public:
	Intern();
	Intern(const Intern &form);
	~Intern();
	Intern & operator = (const Intern &form);

	AForm*	makeForm(std::string nameForm, std::string target);

	class NotAvailableForm : public std::exception {
		private:
			static const char* message;
		public:
			NotAvailableForm() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

#endif