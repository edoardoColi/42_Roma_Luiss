#ifndef HUMANB_HPP
# define HUMANB_HPP

#include <iostream>

#include "Weapon.hpp"

class HumanB
{
private:
	std::string name;
	Weapon* weapon;	//Being a pointer it can also be NULL
public:
	HumanB(std::string name);
	HumanB(const HumanB &humanB);
	~HumanB();
	HumanB & operator = (const HumanB &humanB);
	
	void	attack();
	void	setWeapon(Weapon &weapon);
};

#endif