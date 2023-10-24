/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 18:51:06 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

/*
*/
int main()
{
	try
	{
		Span sp = Span(5); sp.debugListing();
		
		sp.addNumber(6); sp.debugListing();
		sp.addNumber(3); sp.debugListing();
		sp.addNumber(17); sp.debugListing();
		sp.addNumber(9); sp.debugListing();
		sp.addNumber(11); sp.debugListing();

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (Span::SpanIsFullException &e)
	{
		std::cerr << "Catch the SpanIsFullException: " << e.what() << std::endl;
	}
	catch (Span::SizeTooSmallException &e)
	{
		std::cerr << "Catch the SizeTooSmallException: " << e.what() << std::endl;
	}
	std::cout << std::endl;
	try
	{
		Span sp = Span(1); sp.debugListing();

		sp.addNumber(42); sp.debugListing();

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (Span::SpanIsFullException &e)
	{
		std::cerr << "Catch the SpanIsFullException: " << e.what() << std::endl;
	}
	catch (Span::SizeTooSmallException &e)
	{
		std::cerr << "Catch the SizeTooSmallException: " << e.what() << std::endl;
	}
	std::cout << std::endl;
	try
	{
		std::cout << "Creating a long list of (random) numbers" << std::endl;
		Span sp2 = sp2.addRandom(10000);
		// sp2.debugListing();

		std::cout << sp2.shortestSpan() << std::endl;
		std::cout << sp2.longestSpan() << std::endl;
	}
	catch (Span::SpanIsFullException &e)
	{
		std::cerr << "Catch the SpanIsFullException: " << e.what() << std::endl;
	}
	catch (Span::SizeTooSmallException &e)
	{
		std::cerr << "Catch the SizeTooSmallException: " << e.what() << std::endl;
	}

	return 0;
}