/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/08/28 15:35:10 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>

#include "RPN.hpp"

/*
*/
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "The program must take only one argument." << std::endl;
		std::cout << "Usage: " << argv[0] << " \"reverse polish expression\"" << std::endl;
		return 1;
	}
	RPN expression(argv[1]);
	const std::string allowedSymbols = "0123456789 +-*/";
	bool decimal = false;
	
	for (char c : std::string(argv[1])){
		if (allowedSymbols.find(c) == std::string::npos || (std::isdigit(c) && decimal)){
			std::cout << "Error" << std::endl;
			return 1;
		}
		if (std::isdigit(c))
			decimal = true;
		else
			decimal = false;
	}
	try{
		std::cout << expression.calculate() << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}