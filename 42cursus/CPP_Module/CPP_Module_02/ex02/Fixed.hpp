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

	Fixed	operator + (Fixed const &fix);
	Fixed	operator - (Fixed const &fix);
	Fixed	operator * (Fixed const &fix);
	Fixed	operator / (Fixed const &fix);

	bool	operator > (Fixed const &fix) const;
	bool	operator < (Fixed const &fix) const;
	bool	operator >= (Fixed const &fix) const;
	bool	operator <= (Fixed const &fix) const;
	bool	operator == (Fixed const &fix) const;
	bool	operator != (Fixed const &fix) const;

	Fixed	operator ++ ();
	Fixed	operator ++ (int);
	Fixed	operator -- ();
	Fixed	operator -- (int);

	static Fixed const &min(Fixed const &a, Fixed const &b);
	static Fixed const &max(Fixed const &a, Fixed const &b);
	static Fixed &min(Fixed &a, Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);

	float	toFloat(void) const;
	int		toInt(void) const;
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

std::ostream	&operator << (std::ostream &stream, Fixed const &fix);

#endif