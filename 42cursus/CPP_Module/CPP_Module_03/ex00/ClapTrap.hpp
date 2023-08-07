#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{
private:
	std::string	name;
	int		hp;
	int		mana;
	int		ad;
public:
	ClapTrap();
	ClapTrap(const ClapTrap &clapTrap);
	ClapTrap(const std::string name);
	~ClapTrap();
	ClapTrap & operator = (const ClapTrap &clapTrap);

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	std::string	getName() const;
	int		getHp() const;
	int		getMana() const;
	int		getAd() const;
};

std::ostream	&operator << (std::ostream &stream, ClapTrap &clapTrap);

#endif