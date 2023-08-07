#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <iomanip>

class Contact
{
private:
	std::string	first_name;
	std::string	last_name;
	std::string	nickname;
	std::string	phone_number;
	std::string	secret;
public:
	Contact();
	Contact(const Contact &contact);
	~Contact();
	Contact & operator = (const Contact &contact);

	void	fullDisplay();
	void	setAll(std::string fn, std::string lf, std::string nn, std::string pn, std::string sc);
	std::string	getFirstName() const;
	std::string	getLastName() const;
	std::string	getNickname() const;
	std::string	getPhoneNumber() const;
	std::string	getSecret() const;
};

#endif