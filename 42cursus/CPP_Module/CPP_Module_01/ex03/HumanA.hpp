#ifndef HUMANA_HPP
# define HUMANA_HPP

#include <iostream>

#include "Weapon.hpp"

class HumanA
{
private:
	std::string name;
	Weapon& weapon;	//Being a reference it cannot be NULL
public:
	HumanA(std::string name, Weapon& weapon);
	HumanA(const HumanA &humanA);
	~HumanA();
	HumanA & operator = (const HumanA &humanA);
	
	void	attack();
};

#endif