#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal
//'virtual' keyword is used to implement polymorphism, which allows a base class to have specific behavior in derived classes.
{
protected:
	std::string	type;
public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal &wrongAnimal); 
	virtual ~WrongAnimal();		//Virtual destructor
	virtual WrongAnimal & operator = (const WrongAnimal &wrongAnimal);		//Virtual copy assignment operator

	void	makeSound() const;
	std::string	getType() const;
};

std::ostream	&operator << (std::ostream &stream, WrongAnimal &WrongAnimal);

#endif