#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal
//'virtual' keyword is used to implement polymorphism, which allows a base class to have specific behavior in derived classes.
{
protected:
	std::string	type;
public:
	AAnimal();
	AAnimal(const AAnimal &animal); 
	virtual ~AAnimal();		//Virtual destructor
	virtual AAnimal & operator = (const AAnimal &animal);		//Virtual copy assignment operator

	//Is a regular virtual function and not a pure virtual function if has an implementation in the base class(it is not mandatory for derived classes to override it).
	//This is a pure virtual, that has no function body and is intended to serve as a placeholder for a function that must be overridden by derived classes.
	virtual void	makeSound() const = 0;	//To prevent the instantiation of a class directly, you can make it an abstract class by adding a pure virtual function.
	std::string	getType() const;
};

std::ostream	&operator << (std::ostream &stream, const AAnimal &AAnimal);

#endif