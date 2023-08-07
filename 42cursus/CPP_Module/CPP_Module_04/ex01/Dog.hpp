#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"
#include <iostream>
#include <string>

class Dog : public Animal
{
private:
	Brain* brain;
public:
	Dog();
	Dog(const Dog &dog); 
	virtual ~Dog();		//Virtual destructor
	virtual Dog & operator = (const Dog &dog);		//Virtual copy assignment operator

	void	makeSound() const override;
	Brain*	getBrain(void) const;
};

#endif