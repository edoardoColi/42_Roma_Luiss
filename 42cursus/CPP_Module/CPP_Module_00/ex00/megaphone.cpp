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

using namespace std;

/*
*/
int main(int argc, char* argv[])
{
	int	i;
	int	j;
	string str;

	if(argc == 1){
		cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << endl;
	} else {
		i = 1;
		while(argv[i])
		{
			str = argv[i];
			j = 0;
			while(j < str.length()){
				if(isalpha(str[j]))
					cout << (char)toupper(str[j]);
				else
					cout << str[j];
				j++;
			}
		i++;
		}
	cout << endl;
	}
	return 0;
}
