/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/08/28 18:54:29 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//Functions
/*
*/
std::string RPN::calculate()
{
	int counterNum = 0;
	int counterSig = 0;
	std::stack<double> tmp;
	double a, b;
	
	for (char c : std::string(this->expr)){	
		switch (c)
		{
		case '+':
			if(tmp.size() < 2)
				throw WrongExprException();
			counterSig++;
			b = tmp.top(); tmp.pop();
			a = tmp.top(); tmp.pop();
			tmp.push(a + b);
			// std::cout << "(" << a << " + " << b << ") = " << (a + b) << std::endl;
			break;
		case '-':
			if(tmp.size() < 2)
				throw WrongExprException();
			counterSig++;
			b = tmp.top(); tmp.pop();
			a = tmp.top(); tmp.pop();
			tmp.push(a - b);
			// std::cout << "(" << a << " - " << b << ") = " << (a - b) << std::endl;
			break;
		case '*':
			if(tmp.size() < 2)
				throw WrongExprException();
			counterSig++;
			b = tmp.top(); tmp.pop();
			a = tmp.top(); tmp.pop();
			tmp.push(a * b);
			// std::cout << "(" << a << " * " << b << ") = " << (a * b) << std::endl;
			break;
		case '/':
			if(tmp.size() < 2)
				throw WrongExprException();
			counterSig++;
			b = tmp.top(); tmp.pop();
			a = tmp.top(); tmp.pop();
			tmp.push(a / b);
			// std::cout << "(" << a << " / " << b << ") = " << (a / b) << std::endl;
			break;
		default:
			if (std::isdigit(c))
			{
				counterNum++;
				tmp.push(this->polishList.top());
				this->polishList.pop();
			}
			break;
		}
		if (counterNum <= counterSig)
			throw WrongExprException();
	}
	if (tmp.size() != 1)
		throw WrongExprException();
	return std::to_string(tmp.top());
}


//Constructors
RPN::RPN()
: expr("")
{
	// std::cout << "Constructor called(RPN)" << std::endl;
}

RPN::RPN(const std::string expr)
: expr(expr)
{
	std::stack<double> tmp;

	for (char c : std::string(expr)){
		if (std::isdigit(c))
			tmp.push(c - '0');		//transform it into an integer
	}
	while (!tmp.empty()) {		//tmp used for support because I need the numbers from the beginning
		this->polishList.push(tmp.top());
		tmp.pop();
	}
	// std::cout << "Constructor called(RPN)" << std::endl;
}

RPN::RPN(const RPN &rpn)
: expr(rpn.expr)
{
	this->polishList = rpn.polishList;
}

RPN	&RPN::operator = (const RPN &rpn)
{
	this->~RPN();
	::new(this) RPN(rpn);
	return (*this);
}

//Destructor
RPN::~RPN()
{
	// std::cout << "Destructor called(RPN)" << std::endl;
}

//Setters

//Getters

//Exceptions
const char* RPN::WrongExprException::message = "The expression is not valid, provide another one.";
const char * RPN::WrongExprException::what() const throw()
{
	return this->message;
}
