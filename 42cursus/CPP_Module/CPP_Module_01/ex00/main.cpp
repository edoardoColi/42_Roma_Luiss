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

#include "Zombie.hpp"

/*
Object Lifetime: Objects allocated on the STACK have automatic storage
duration and are destroyed when they go out of scope. If the lifetime
of the object is limited to a specific scope or a function, it is generally
better to allocate it on the STACK. However, if the object needs to persist
beyond the scope of its creation or if its lifetime is dynamically
determined, HEAP allocation may be more appropriate.
*/
int main(void)
{
	std::string name;

	std::cout << "(Now creating zombie on the heap)." << std::endl;
	std::cout << "Zombie name: " << std::flush;//perche importante flush?
	std::cin >> name;
	Zombie* zombiHeap = newZombie(name);
	zombiHeap->announce();
	delete zombiHeap;

	std::cout << "(Now creating zombie on the stack)." << std::endl;
	std::cout << "Insert Zombie name: " << std::flush;//perche importante flush?
	std::cin >> name;
	Zombie zombiStack(name);
	zombiStack.announce();
	
	std::cout << "(Now creating zombie on the heap)." << std::endl;
	std::cout << "Zombie name: " << std::flush;//perche importante flush?
	std::cin >> name;
	randomChump(name);
	std::cout << "No more zombies spawning." << std::endl;
	return 0;
}