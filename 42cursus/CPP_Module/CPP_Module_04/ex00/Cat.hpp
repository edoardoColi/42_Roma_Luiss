#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include <iostream>
#include <string>

class Cat : public Animal
{
public:
	Cat();
	Cat(const Cat &cat); 
	virtual ~Cat();
	virtual Cat & operator = (const Cat &cat);

	void	makeSound() const override;
};

#endif