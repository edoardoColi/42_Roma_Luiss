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

#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"

/*
*/
int main(void)
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound(); //will output the dog sound!
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	const WrongAnimal* noMeta = new WrongAnimal();
	const WrongAnimal* noI = new WrongCat();
	const WrongCat* siI = new WrongCat();
	std::cout << noI->getType() << " " << std::endl;
	std::cout << siI->getType() << " " << std::endl;
	noMeta->makeSound();
	noI->makeSound(); //will not output the wrontcat sound!
	siI->makeSound();

	delete noMeta;
	delete noI;
	delete siI;

	return (0);
}