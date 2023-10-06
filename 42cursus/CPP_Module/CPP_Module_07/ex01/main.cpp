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

#include "iter.hpp"

// class Awesome
// {
// private:
// 	int	_n;
// public:
// 	Awesome(void):_n(42) {return;}

// 	int get(void) const {return this->_n;}
// };
// std::ostream & operator << (std::ostream &o, const Awesome &rhs) {o << rhs.get(); return o;}
// template<typename T>
// void printa(T const &x) {std::cout << x << std::endl; return;}

void doouble(int const &n);
void print(std::string const &n);

/*
*/
int main(int argc, char *argv[]) 
{
	int arr[] = {1, 2, 3, 21, 5};
	::iter(arr, 5, doouble);
	std::string arr2[] = {"pizza", "pasta", "mandolino", "mafia", "colosseo"};
	::iter(arr2, 5, print);
	return 0;

	// int tab[] = {0, 1, 2, 3, 4};
	// Awesome tab2[5];

	// iter(tab, 5, printa);
	// iter(tab2, 5, printa);
	// return 0;
}

/*
*/
void doouble(int const &n)
{
	std::cout << n*2 << std::endl;
}

/*
*/
void print(std::string const &str)
{
	std::cout << str << std::endl;
}
