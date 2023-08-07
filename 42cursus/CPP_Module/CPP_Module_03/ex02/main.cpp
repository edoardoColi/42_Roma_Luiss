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

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

/*
*/
int main(void)
{
	FragTrap	FragtrapA("Fragtrap_1");
	FragTrap	FragtrapB("Fragtrap_2");
	FragtrapA.highFivesGuys();
	FragtrapB.highFivesGuys();
	std::cout << FragtrapA << "\n" << FragtrapB << std::endl;

	FragtrapA.attack("Fragtrap_2");
	FragtrapB.takeDamage(FragtrapA.getAd());
	FragtrapA.beRepaired(5);
	std::cout << FragtrapA << "\n" << FragtrapB << std::endl;

	FragtrapB.takeDamage(120);
	FragtrapB.beRepaired(200);
	std::cout << FragtrapA << "\n" << FragtrapB << std::endl;
	
	return (0);
}