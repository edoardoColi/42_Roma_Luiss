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

#define SIZE 6

/*
*/
int main(void)
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;//should not create a leak
	delete i;

	std::cout << "######################## Mandatory ########################" << std::endl;
	Animal *tab[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << i+1 <<" ----------------------------------" << std::endl;
		if (i % 2 == 0)
		{
			tab[i] = new Dog();
			tab[i]->makeSound();
		}
		else
		{
			tab[i] = new Cat();
			tab[i]->makeSound();
		}
	}
	std::cout << "########## End filling #############" << std::endl << "#" << std::endl << "########## Start deleting ##########" << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << i+1 <<" ----------------------------------" << std::endl;
		delete tab[i];
	}
	std::cout << "###########################################################" << std::endl;

	Animal t;
	const Animal* q = new Animal();
	Cat c;
	Animal* h = new Cat();

	(*(c.getBrain())).setIdea("casa",1);
	std::cout << std::endl;

	std::cout << t << std::endl;
	std::cout << *q << std::endl;
	std::cout << *(c.getBrain()) << std::endl;
	std::cout << (*(c.getBrain())).getIdea(1) << std::endl;
	std::cout << *h << std::endl;

	std::cout << std::endl;

	delete q;
	delete h;

	Cat basico;
	Cat tmpo;

	(*(basico.getBrain())).setIdea("I will", 0);
	(*(basico.getBrain())).setIdea("kill them", 1);
	(*(basico.getBrain())).setIdea("all", 2);

	tmpo = basico;
	
	std::cout << basico << std::endl << *basico.getBrain() << std::endl;
	std::cout << tmpo << std::endl << *tmpo.getBrain() << std::endl;

	(*(basico.getBrain())).setIdea("IS A JOKE", 3);

	std::cout << basico << std::endl << *basico.getBrain() << std::endl;
	std::cout << tmpo << std::endl << *tmpo.getBrain() << std::endl;

	// Dog basic;
	// {
	// 	Dog tmp = basic;
	// }

	std::cout << "########## The End ##########" << std::endl;
	return (0);
}