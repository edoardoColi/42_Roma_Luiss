/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 00:45:56 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

/*
*/
int main(int argc, char* argv[])
{
	int	i;
	int	j;
	std::string str;

	if(argc == 1){
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	} else {
		i = 1;
		while(argv[i])
		{
			str = argv[i];
			j = 0;
			while(j < str.length()){
				if(isalpha(str[j]))
					std::cout << (char)toupper(str[j]);
				else
					std::cout << str[j];
				j++;
			}
		i++;
		}
	std::cout << std::endl;
	}
	return 0;
}
