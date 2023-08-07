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

#include "ClapTrap.hpp"

/*
*/
int main(void)
{
	ClapTrap	ClaptrapA("Claptrap_1");
	ClapTrap	ClaptrapB("Claptrap_2");
	std::cout << ClaptrapA << "\n" << ClaptrapB << std::endl;

	ClaptrapA.attack("Claptrap_2");
	ClaptrapB.takeDamage(ClaptrapA.getAd());
	ClaptrapA.beRepaired(5);
	std::cout << ClaptrapA << "\n" << ClaptrapB << std::endl;

	ClaptrapB.takeDamage(12);
	ClaptrapB.beRepaired(20);
	std::cout << ClaptrapA << "\n" << ClaptrapB << std::endl;
	
	return (0);
}