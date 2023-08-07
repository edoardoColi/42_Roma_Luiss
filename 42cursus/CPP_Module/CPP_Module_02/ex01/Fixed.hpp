#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
	int	number;
	static const int bits = 8;
public:
	Fixed();
	Fixed(const Fixed &fix);
	Fixed(const int integer);
	Fixed(const float floating);
	~Fixed();
	Fixed & operator = (const Fixed &fix);

	float	toFloat(void) const;
	int		toInt(void) const;
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

std::ostream	&operator << (std::ostream &stream, Fixed const &fix);

#endif