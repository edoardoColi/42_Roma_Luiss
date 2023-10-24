#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iomanip>
# include <exception>
# include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <ctime>
# include <map>

class BitcoinExchange
{
private:
	std::string const csv;
	std::map<std::string, float> marketFloatings;

	std::string	readFile(std::string name);
	int	checkLine(std::string name);
public:
	BitcoinExchange();
	BitcoinExchange(const std::string csvFile);
	BitcoinExchange(const BitcoinExchange &BitcoinExchange);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &BitcoinExchange);

	float getDateValue(const std::string date);
	std::string performExchange(const std::string line);

	class CSVException : public std::exception {
		private:
			static const char* message;
		public:
			CSVException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

#endif
