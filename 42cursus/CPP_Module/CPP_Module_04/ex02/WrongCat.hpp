#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"
#include <iostream>
#include <string>

class WrongCat : public WrongAnimal
{
public:
	WrongCat();
	WrongCat(const WrongCat &wrongCat);
	virtual ~WrongCat();		//Virtual destructor
	virtual WrongCat & operator = (const WrongCat &wrongCat);		//Virtual copy assignment operator

	void	makeSound() const;
};

#endif