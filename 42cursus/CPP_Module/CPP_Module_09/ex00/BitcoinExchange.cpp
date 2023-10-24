/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/08/25 16:13:08 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//Functions
/*
*/
std::string	BitcoinExchange::readFile(std::string name)
{
	std::string		text("");
	std::string		buffer;
	std::ifstream	file(name);

	if (file.is_open()) {
		while (std::getline(file, buffer))
			text += buffer + "\n";
		file.close();
	} else {
		std::cout << "Can't use " << name << " file." << std::endl;
		throw CSVException();
	}
	return text;
}

/*
*/
int BitcoinExchange::checkLine(std::string str)
{
	std::istringstream	issline(str);
	std::string			date, year, month, day;
	float				value;

	// }

	if (str.find(" | ") != std::string::npos) {
		date = str.substr(0, str.find_first_of(" | "));
		if (date.empty())
			return 1;
			
		size_t firstDash = date.find('-');
		size_t secondDash = date.find('-', firstDash + 1);

		year = date.substr(0, firstDash);
		month = date.substr(firstDash + 1, secondDash - firstDash - 1);
		day = date.substr(secondDash + 1);
		try{
			struct std::tm timeinfo = {};
			timeinfo.tm_year = std::stoi(year);
			timeinfo.tm_mon = std::stoi(month) - 1;    //Months are 0-11
			timeinfo.tm_mday = std::stoi(day);
			if (!(timeinfo.tm_year >= 0 && timeinfo.tm_mon >= 0 && timeinfo.tm_mon <= 11 && timeinfo.tm_mday > 0 && timeinfo.tm_mday <= 31 && mktime(&timeinfo) != -1)) {	//check if the std::tm structure timeinfo represents a valid date
				return 1;
			}
		} catch(const std::exception& e){
			return 1;
		}
		try{
			value = std::stof(str.substr(str.find_first_of(" | ") + 3));
		} catch(const std::exception& e){
			return 2;
		}
		if (value <= 0.f || value > 1000.f){
			return 2;
		}
	} else {
		return 3;
	}
	return 0;
}

/*
constrain ogni linea del file stesso modo
*/
std::string BitcoinExchange::performExchange(const std::string line)
{
	std::string			ret("");
	std::string			date, target;
	int					year, month, day;
	float				value;

	switch (checkLine(line))
	{
		case 1:
			ret = "(" + line + ")" + std::string(42, ' ') + "<Error: A valid date will always be in the following format: Year-Month-Day>";
			break;
		case 2:
			ret = "(" + line + ")" + std::string(42, ' ') + "<Error: A valid value must be either a float or a positive integer between 0 and 1000>";
			break;
		case 3:
			ret = "(" + line + ")" + std::string(42, ' ') + "<Error: Each line in this file must use the following format: \"date | value\">";
			break;
		default:
			date = line.substr(0, line.find_first_of(" | "));
			value = std::stof(line.substr(line.find_first_of(" | ") + 3));
			ret = date + " => " + std::to_string(value) + " = " + std::to_string(value * this->getDateValue(date));
			// size_t firstDash = date.find('-');
			// size_t secondDash = date.find('-', firstDash + 1);
			// year = std::stoi(date.substr(0, firstDash));
			// month = std::stoi(date.substr(firstDash + 1, secondDash - firstDash - 1));
			// day = std::stoi(date.substr(secondDash + 1));
			// target = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
			// ret = target + " => " + std::to_string(value) + " = " + std::to_string(value * this->getDateValue(target));
			break;
	}
	return(ret);
}

//Constructors
BitcoinExchange::BitcoinExchange()
: csv("")
{
	throw CSVException();
	// std::cout << "Constructor called(BitcoinExchange)" << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string csvFile)
: csv(readFile(csvFile))
{
	std::istringstream iss(csv);
	std::string line;

	std::getline(iss, line, '\n');	//to skip the first line, where the description of the columns is located
	while (std::getline(iss, line, '\n')) {
		std::istringstream lineStream(line);
		std::string data, value;
		if (std::getline(lineStream, data, ',') && std::getline(lineStream, value)) {
			try {
				std::stof(value);}
			catch(const std::exception& e) {
				throw CSVException();}
			this->marketFloatings[data] = std::stof(value);
		}
	}
	// std::cout << "Constructor called(BitcoinExchange)" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &bitcoinExchange)
: csv(bitcoinExchange.csv)
{
	this->marketFloatings = bitcoinExchange.marketFloatings;
}

BitcoinExchange	&BitcoinExchange::operator = (const BitcoinExchange &bitcoinExchange)
{
	this->~BitcoinExchange();
	::new(this) BitcoinExchange(bitcoinExchange);
	return (*this);
}

//Destructor
BitcoinExchange::~BitcoinExchange()
{
	// std::cout << "Destructor called(BitcoinExchange)" << std::endl;
}

//Setters

//Getters
float BitcoinExchange::getDateValue(const std::string date)
{
	float deft(0);

	for (std::map<std::string, float>::const_reverse_iterator it = this->marketFloatings.rbegin(); it != this->marketFloatings.rend(); ++it){
		if (it->first <= date && deft == 0.0f){
			deft = it->second;
			break;
		}
	}
	return deft;
}

//Exceptions
const char* BitcoinExchange::CSVException::message = "A proper file CSV is needed.";
const char * BitcoinExchange::CSVException::what() const throw()
{
	return this->message;
}
