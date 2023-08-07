#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie
{
private:
	std::string name;
public:
	Zombie(std::string name);
	Zombie(const Zombie &zombie);
	~Zombie();
	Zombie & operator = (const Zombie &zombie);
	
	void	announce( void );
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif