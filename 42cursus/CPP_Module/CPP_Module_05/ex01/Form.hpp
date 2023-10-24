#ifndef FORM_HPP
# define FORM_HPP

#include <exception>
#include <iostream>
#include <string>
#include "Bureaucrat.hpp"
class Bureaucrat;	//Forward declaration for circular dependencies between header files

class Form
{
private:
	std::string	const name;
	bool	signedForm;
	int	const gradeLevelToSign;
	int	const gradeLevelToExecution;

public:
	Form();
	Form(std::string name, int signGrade, int execGrade);
	Form(const Form &form);
	~Form();
	Form &operator=(const Form &form);

	void	beSigned(Bureaucrat &bureaucrat);
	std::string	getName() const;
	int		isSigned() const;
	int		getSignGrade() const;
	int		getExecGrade() const;

	class GradeTooHighException : public std::exception {
		private:
			static const char* message;
		public:
			GradeTooHighException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
	class GradeTooLowException : public std::exception {
		private:
			static const char* message;
		public:
			GradeTooLowException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

std::ostream & operator << (std::ostream &stream, Form &form);

#endif