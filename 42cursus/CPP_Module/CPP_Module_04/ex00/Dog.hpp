#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include <iostream>
#include <string>

class Dog : public Animal
{
public:
	Dog();
	Dog(const Dog &dog); 
	virtual ~Dog();
	virtual Dog & operator = (const Dog &dog);

	void	makeSound() const override;
};

#endif