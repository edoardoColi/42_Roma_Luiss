/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 17:40:15 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

//Functions
/*
*/
uintptr_t Serializer::serialize(Data *ptr) 
{
	return reinterpret_cast<uintptr_t>(ptr);	//reinterpret cast is used to convert one pointer type to another, even if the type are unrelated
}

/*
*/
Data* Serializer::deserialize(uintptr_t raw) 
{
	return reinterpret_cast<Data*>(raw);	//reinterpret cast is used to convert one pointer type to another, even if the type are unrelated
}

//Constructors
Serializer::Serializer()
{
	std::cout << "Constructor called(Serializer)" << std::endl;
}

Serializer::Serializer(const Serializer &serializer)
{
	*this = serializer;
}

Serializer	&Serializer::operator = (const Serializer &serializer)
{
	return *this;
}

//Destructor
Serializer::~Serializer()
{
	std::cout << "Destructor called(Serializer)" << std::endl;
}

//Setters

//Getters
