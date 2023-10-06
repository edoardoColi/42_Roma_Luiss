/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

//Functions
/*
*/
void	Span::addNumber(unsigned int n)
{
	if (this->head.size() >= this->n)
		throw Span::SpanIsFullException();
	this->head.push_back(n);
}

/*
*/
Span	Span::addRandom(unsigned int n)
{
	srand(time(NULL));
	Span tmp = Span(n);
	for (size_t i = 0; i < n; i++)
		tmp.head.push_back(rand());
	return tmp;
}

/*
*/
int		Span::shortestSpan()
{
	unsigned int	min;
	unsigned int	dist;

	if (this->n < 2)
		throw Span::SizeTooSmallException();
	std::vector<int> tmp(this->head.begin(), this->head.end());	//support array to calculate the min span
	std::sort(tmp.begin(), tmp.end());
	min = std::abs(tmp[1] - tmp[0]);
	for (size_t i = 1; i < tmp.size() - 1; ++i)
	{
		dist = std::abs(tmp[i + 1] - tmp[i]);
		if (dist < min)
			min = dist;
	}
	return (min);
}

/*
*/
int		Span::longestSpan()
{
	unsigned int	max = *std::max_element(this->head.begin(), this->head.end());
	unsigned int	min = *std::min_element(this->head.begin(), this->head.end());
	return max - min;
}

/*
*/
void	Span::debugListing()
{
	int i = 0;
	std::cout << "  DEBUG LIST: ";
	for (const int& value : this->head) {
		std::cout << value << "->";
		i++;
	}
	std::cout << "NULL" << std::endl;
}

//Constructors
Span::Span()
{
	std::cout << "Constructor called(Span)" << std::endl;
}

Span::Span(unsigned int n)
{
	this->n = n;
	std::cout << "Constructor called(Span)" << std::endl;
}

Span::Span(const Span &span)
{
	*this = span;
}

Span	&Span::operator = (const Span &span)
{
	this->n = span.n;
	this->head = span.head;
	return *this;
}

//Destructor
Span::~Span()
{
	std::cout << "Destructor called(Span)" << std::endl;
}

//Setters

//Getters

//Exceptions
const char* Span::SpanIsFullException::message = "Can't be added one more number, too much elements.";
const char * Span::SpanIsFullException::what() const throw() 
{
	return this->message;
}

const char* Span::SizeTooSmallException::message = "Cant calculate the span, not enough elements.";
const char * Span::SizeTooSmallException::what() const throw() 
{
	return this->message;
}
