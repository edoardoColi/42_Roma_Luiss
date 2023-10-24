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

#include <iostream>
#include <ctime>

class Base{ public: virtual ~Base(){} };
class A : public Base {};
class B : public Base {};
class C : public Base {};

Base*	generate(void);
void	identify(Base* p);
void	identify(Base& p);

/*
*/
int main(int argc, char *argv[]) 
{
	srand(time(NULL));
	
	Base*	primo = generate();
	Base*	secondo = generate();
	Base*	terzilio = generate();
	Base*	quartilio = generate();

	std::cout << "/* ######################################### */\n" << std::endl;
	std::cout << "primo* = "; identify( primo ); std::cout << std::endl;
	std::cout << "primo& = "; identify( *primo ); std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "secondo* = "; identify( secondo ); std::cout << std::endl;
	std::cout << "secondo& = "; identify( *secondo ); std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "terzilio* = "; identify( terzilio ); std::cout << std::endl;
	std::cout << "terzilio& = "; identify( *terzilio ); std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "quartilio* = "; identify( quartilio ); std::cout << std::endl;
	std::cout << "quartilio& = "; identify( *quartilio ); std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "/* ######################################### */" << std::endl;

	delete primo;
	delete secondo;
	delete terzilio;
	delete quartilio;

	return (0);
}

/*
*/
Base*	generate(void)
{
	switch (rand() % 3)
	{
		case 0:
			return (new A);
			break;
		case 1:
			return (new B);
			break;
		case 2:
			return (new C);
			break;
		default:
			return (NULL);
	}
}

/*
*/
void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))	//dynamic cast is used, primarily for dealing within polymorphism, to convert pointers or references of base class to derived class. It performs a runtime check to ensure that the cast is valid
		std::cout << "A";
	else if (dynamic_cast<B*>(p))//dynamic cast is used, primarily for dealing within polymorphism, to convert pointers or references of base class to derived class. It performs a runtime check to ensure that the cast is valid
		std::cout << "B";
	else if (dynamic_cast<C*>(p))//dynamic cast is used, primarily for dealing within polymorphism, to convert pointers or references of base class to derived class. It performs a runtime check to ensure that the cast is valid
		std::cout << "C";
	else
		std::cout << "Undefined cast";
}

/*
*/
void	identify(Base& p)
{
	try
	{
		A &a = dynamic_cast<A&>(p);//dynamic cast is used, primarily for dealing within polymorphism, to convert pointers or references of base class to derived class. It performs a runtime check to ensure that the cast is valid
		std::cout << "A";
	}
	catch(const std::exception& e){
		try
		{
			B &b = dynamic_cast<B&>(p);//dynamic cast is used, primarily for dealing within polymorphism, to convert pointers or references of base class to derived class. It performs a runtime check to ensure that the cast is valid
			std::cout << "B";
		}
		catch(const std::exception& e){
			try
			{
				C &c = dynamic_cast<C&>(p);//dynamic cast is used, primarily for dealing within polymorphism, to convert pointers or references of base class to derived class. It performs a runtime check to ensure that the cast is valid
				std::cout << "C";
			}
			catch(const std::exception& e){
				std::cout << "Exceptions catched: " << e.what() << std::endl;
			}
		}
	}
}
