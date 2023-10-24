#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

//'template' keyword is used to define a generic pattern thet the compiler can use to generate specific version of the functions or class for different data types
template<typename T>	//T is used as a placeholder for the actual data type that will be used when the function is invoked
void swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
const T& min(const T& x, const T& y)
{
	return ((x < y) ? x : y);
}

template<typename T>
const T& max(const T& x, const T& y)
{
	return ((x > y) ? x : y);
}

#endif
