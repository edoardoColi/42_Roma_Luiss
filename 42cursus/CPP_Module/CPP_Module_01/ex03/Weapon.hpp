#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon
{
private:
	std::string type;
public:
	Weapon(std::string type);
	Weapon(const Weapon &weapon);
	~Weapon();
	Weapon & operator = (const Weapon &weapon);
	
	void			setType(std::string type);
	const std::string&	getType() const;
};

#endif