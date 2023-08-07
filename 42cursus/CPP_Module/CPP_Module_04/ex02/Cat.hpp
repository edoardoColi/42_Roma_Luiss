#ifndef CAT_HPP
# define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"
#include <iostream>
#include <string>

class Cat : public AAnimal
{
private:
	Brain* brain;
public:
	Cat();
	Cat(const Cat &cat); 
	virtual ~Cat();		//Virtual destructor
	virtual Cat & operator = (const Cat &cat);		//Virtual copy assignment operator

	void	makeSound() const override;
	Brain*	getBrain(void) const;
};

#endif