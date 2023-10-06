#ifndef RPN_HPP
# define RPN_HPP

# include <exception>
# include <iostream>
# include <string>
# include <stack>

class RPN
{
private:
	std::string const expr;
	std::stack<double> polishList;

public:
	RPN();
	RPN(const std::string expr);
	RPN(const RPN &rpn);
	~RPN();
	RPN &operator=(const RPN &rpn);

	std::string calculate();

	class WrongExprException : public std::exception {
		private:
			static const char* message;
		public:
			WrongExprException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

#endif
