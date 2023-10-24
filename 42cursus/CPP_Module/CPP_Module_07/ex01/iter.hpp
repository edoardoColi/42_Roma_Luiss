#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <string>

//'template' keyword is used to define a generic pattern thet the compiler can use to generate specific version of the functions or class for different data types
template<typename T>	//T is used as a placeholder for the actual data type that will be used when the function is invoked
void iter(T* arrayHead, size_t size, void(*f)(T const &))
{
	for (size_t i = 0; i < size; i++)
	{
		f(arrayHead[i]);
	}
}

#endif
