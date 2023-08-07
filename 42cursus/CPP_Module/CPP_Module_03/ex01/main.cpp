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

/*
*/
int main(void)
{
	ScavTrap	ScavtrapA("Scavtrap_1");
	ScavTrap	ScavtrapB("Scavtrap_2");
	ScavtrapA.guardGate();
	ScavtrapB.guardGate();
	std::cout << ScavtrapA << "\n" << ScavtrapB << std::endl;

	ScavtrapA.attack("Scavtrap_2");
	ScavtrapB.takeDamage(ScavtrapA.getAd());
	ScavtrapA.beRepaired(5);
	std::cout << ScavtrapA << "\n" << ScavtrapB << std::endl;

	ScavtrapB.takeDamage(120);
	ScavtrapB.beRepaired(200);
	std::cout << ScavtrapA << "\n" << ScavtrapB << std::endl;
	
	return (0);
}