#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <string>

class Brain
{
private:
	std::string	ideas[100];
public:
	Brain();
	Brain(const Brain &brain); 
	~Brain();
	Brain & operator = (const Brain &brain);

	void	setIdea(std::string idea, int n);
	std::string	getIdea(int n) const;
};

std::ostream	&operator << (std::ostream &stream, const Brain &brain);

#endif