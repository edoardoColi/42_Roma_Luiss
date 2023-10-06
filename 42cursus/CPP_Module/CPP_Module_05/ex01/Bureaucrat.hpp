#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <exception>
#include <iostream>
#include <string>
#include "Form.hpp"
class Form;	//Forward declaration for circular dependencies between header files

class Bureaucrat
{
private:
	std::string	const name;
	int	grade;
public:
	Bureaucrat();
	Bureaucrat(std::string name, int grade);
	Bureaucrat(const Bureaucrat &bureaucrat); 
	~Bureaucrat();
	Bureaucrat &operator=(const Bureaucrat &bureaucrat);

	void	incrementGrade();
	void	decrementGrade();
	void	signForm(Form &form);
	std::string	getName() const;
	int		getGrade() const;
	void	setGrade(int const n);

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

std::ostream & operator << (std::ostream &stream, Bureaucrat &bureaucrat);

#endif