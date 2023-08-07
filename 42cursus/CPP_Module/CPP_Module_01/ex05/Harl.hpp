#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>

class Harl
{
private:
	void	(Harl::*complains[4])(void);
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
public:
	Harl();
	Harl(const Harl &harl);
	~Harl();
	Harl & operator = (const Harl &harl);

	void	complain(std::string level);
};

#endif