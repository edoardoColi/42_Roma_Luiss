/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 18:51:06 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

// class Awesome
// {
// private:
// 	int	_n;
// public:
// 	Awesome(void):_n(0) {}
// 	Awesome(int n):_n(n) {}
// 	Awesome & operator = (Awesome &a) {_n = a._n;return *this;}
// 	bool operator == (Awesome const &rhs) const {return(this->_n == rhs._n);}
// 	bool operator != (Awesome const &rhs) const {return(this->_n != rhs._n);}
// 	bool operator > (Awesome const &rhs) const {return(this->_n > rhs._n);}
// 	bool operator < (Awesome const &rhs) const {return(this->_n < rhs._n);}
// 	bool operator >= (Awesome const &rhs) const {return(this->_n >= rhs._n);}
// 	bool operator <= (Awesome const &rhs) const {return(this->_n <= rhs._n);}

// 	int get_n() const {return _n;}
// };
// std::ostream & operator << (std::ostream &o, const Awesome &a) {o << a.get_n(); return o;}

/*
*/
int main(int argc, char *argv[]) 
{
	int a = 2;
	int b = 3;

	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min( a, b ) << std::endl;
	std::cout << "max(a, b) = " << ::max( a, b ) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min( c, d ) << std::endl;
	std::cout << "max(c, d) = " << ::max( c, d ) << std::endl;

	return 0;

	// Awesome a(2), b(4);
	// swap(a,b);
	// std::cout << a << " " << b << std::endl;
	// std::cout << max(a, b) << std::endl;
	// std::cout << min(a, b) << std::endl;
	
	// return 0;
}