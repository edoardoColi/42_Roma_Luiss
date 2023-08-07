#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <iostream>
#include <string>

class ScavTrap: virtual public ClapTrap	//Virtual inheritance is used to solve the "diamond inheritance" problem in C++.
//'using' keyword is used in the derived class to import specific members of the base classes into its scope, making them accessible directly within the derived class.
{
public:
	ScavTrap();
	ScavTrap(const ScavTrap &scavTrap);
	ScavTrap(const std::string name);
	~ScavTrap();
	ScavTrap & operator = (const ScavTrap &scavTrap);

	void	attack(const std::string& target);
	void	guardGate();
};

#endif