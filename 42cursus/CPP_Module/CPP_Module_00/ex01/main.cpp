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

#include <iostream>
#include <iomanip>
#include <limits>

#include "PhoneBook.hpp"

/*
*/
int main(int argc, char* argv[])
{
	int			index;
	std::string		request;
	std::string		param[5];
	PhoneBook	rubrica;

	std::cout << "> Which are your intentions?" << std::endl << "> ";
	getline(std::cin, request);
	while(1)
	{
		if(request.compare("EXIT") == 0) {
			break;
		} else if(request.compare("ADD") == 0) {
			for(int i = 0; i < 5; i++){
				if(i == 0) std::cout << "< Give me the first name: ";
				if(i == 1) std::cout << "< Give me the last name: ";
				if(i == 2) std::cout << "< Give me the nickname: ";
				if(i == 3) std::cout << "< Give me the phone number: ";
				if(i == 4) std::cout << "< Give me the secret: ";
				while(1)
				{
					std::cin.clear();//[Re]sets the error state. (Why necessary?)
					if(	getline(std::cin, param[i]) && !param[i].empty())
						break;
					if (!std::cin.good()) {
						std::cout << std::endl;
						return 1;
					}
					std::cout << "< Cannot be empty: ";
				}
			}
			rubrica.addContact(param[0], param[1], param[2], param[3], param[4]);
		} else if(request.compare("SEARCH") == 0) {
			rubrica.list();
			std::cout << "< Enter index: ";
			while(1)
			{
				getline(std::cin, request);
				if((index = atoi(request.c_str())) > 0 && rubrica.printContact(index) == 0)//I don't use stoi() because it handles things that aren't numbers by raising an exception
					break;
				std::cout << "< Enter valid index: ";
			}
		} else {
			std::cout << "< Not something I can handle" << std::endl;
			rubrica.usage();
		}
		std::cout << "> Which are your intentions?" << std::endl << "> ";
		getline(std::cin, request);
	}
	return 0;
}
