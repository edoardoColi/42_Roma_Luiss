#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int	number;
	static const int bits = 8;
public:
	Fixed();
	Fixed(const Fixed &fix);
	~Fixed();
	Fixed & operator = (const Fixed &fix);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

#endif