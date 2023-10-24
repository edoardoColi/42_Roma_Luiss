#ifndef AFORM_HPP
# define AFORM_HPP

#include <exception>
#include <iostream>
#include <string>
#include "Bureaucrat.hpp"
class Bureaucrat;	//Forward declaration for circular dependencies between header files

class AForm
{
private:
	std::string	const name;
	bool	signedForm;
	int	const gradeLevelToSign;
	int	const gradeLevelToExecution;

public:
	AForm();
	AForm(std::string name, int signGrade, int execGrade);
	AForm(const AForm &form);
	virtual ~AForm();
	AForm & operator = (const AForm &form);

	void	beSigned(Bureaucrat &bureaucrat);
	virtual void	execute(Bureaucrat const &executor) const = 0;	//To prevent the instantiation of a class directly, you can make it an abstract class by adding a pure virtual function.
	virtual AForm*	clone(std::string target) = 0;
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
	class ExecutionException : public std::exception {
		private:
			static const char* message;
		public:
			ExecutionException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

std::ostream & operator << (std::ostream &stream, AForm &form);

#endif