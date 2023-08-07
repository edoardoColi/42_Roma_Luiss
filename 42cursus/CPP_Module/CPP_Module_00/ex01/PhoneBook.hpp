#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>

#include "Contact.hpp"

#define MAX_ENTRYS 8

class PhoneBook
{
private:
	Contact	entry[MAX_ENTRYS];
	int		lastPos;
	int		firstPos;
public:
	PhoneBook();
	PhoneBook(const PhoneBook &phoneBook);
	~PhoneBook();
	PhoneBook & operator = (const PhoneBook &phoneBook);

	void	usage();
	void	addContact(std::string fn, std::string lf, std::string nn, std::string pn, std::string sc);
	void	list();
	int		printContact(int i);
};

#endif