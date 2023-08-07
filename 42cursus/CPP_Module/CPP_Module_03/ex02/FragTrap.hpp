#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include <iostream>
#include <string>

class FragTrap: virtual public ClapTrap	//Virtual inheritance is used to solve the "diamond inheritance" problem in C++.
//'using' keyword is used in the derived class to import specific members of the base classes into its scope, making them accessible directly within the derived class.
{
public:
	FragTrap();
	FragTrap(const FragTrap &fragTrap); 
	FragTrap(const std::string name);
	~FragTrap();
	FragTrap & operator = (const FragTrap &fragTrap);

	void	highFivesGuys(void);
};

#endif