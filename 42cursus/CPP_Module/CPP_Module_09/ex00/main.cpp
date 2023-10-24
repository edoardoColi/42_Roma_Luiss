/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/08/28 01:23:31 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>

#include "BitcoinExchange.hpp"

/*
*/
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "The program must take a file as argument." << std::endl;
		std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
		return 1;
	}

	std::string database = "./data.csv";
	std::ifstream file(argv[1]);
	
	if (file.is_open()) {
		file.close();
	} else {
		std::cout << "Can't find " << argv[1] << " file." << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange exng(database);
		std::string		buffer;
		std::ifstream	file(argv[1]);

		if (file.is_open()) {
			std::getline(file, buffer);		//to skip the first line, where the description of the columns is located
			while (std::getline(file, buffer))
				std::cout << exng.performExchange(buffer) << std::endl;
			file.close();
		} else {
			std::cout << "Can't use " << argv[1] << " file." << std::endl;
			return 1;
		}
	}
	catch (std::exception &e) 
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}