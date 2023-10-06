#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <iostream>//todo per cosa viene messo
#include <vector>//scrivere ad esempio: classe vector o cose simili
#include <list>
#include <algorithm>

//'template' keyword is used to define a generic pattern thet the compiler can use to generate specific version of the functions or class for different data types
template<typename T>	//T is used as a placeholdet for the actual data type that will be used when the function is invoked
/*
*/
std::string easyFind(T& haystack, int needle)
{
	if(std::find(haystack.begin(), haystack.end(), needle) != haystack.end())
		return "Element find.";
	return "Element NOT find.";
} 
#endif
