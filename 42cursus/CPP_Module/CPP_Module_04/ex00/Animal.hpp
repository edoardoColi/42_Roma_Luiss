#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal
//'virtual' keyword is used to implement polymorphism, which allows a base class to have specific behavior in derived classes.
{
protected:
	std::string	type;
public:
	Animal();
	Animal(const Animal &animal);
	virtual ~Animal();		//Virtual destructor
	virtual Animal & operator = (const Animal &animal);		//Virtual copy assignment operator

	virtual void	makeSound() const;
	std::string	getType() const;
};

std::ostream	&operator << (std::ostream &stream, Animal &Animal);

#endif