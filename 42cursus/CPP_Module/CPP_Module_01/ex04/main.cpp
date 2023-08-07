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
#include <fstream>
#include <string>

static int	myreplace(std::string file, std::string s1, std::string s2);

/*
*/
int main(int argc, char* argv[])
{
	if (argc == 4) 
	{
		if (!argv[2][0] || !argv[3][0])
		{
			std::cerr << "Strings can not be empty" << std::endl;
			return 1;
		} else
		{
			if (myreplace(argv[1], argv[2], argv[3]) == 1)
				return 1;
		}
	} else
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <old_word> <new_word>" << std::endl;
		return 1;
	}
	return 0;
}

/*
*/
static int	myreplace(std::string file, std::string s1, std::string s2) 
{
	std::fstream	old_file;
	std::fstream	new_file;
	std::string	line;
	std::string	tmp;
	size_t	find_value;

	old_file.open(file.c_str(), std::ios::in);
	if (!old_file)
	{
		std::cerr << "The input file could not be opened" << std::endl;
		return 1;
	}
	new_file.open(std::string(file + ".replace").c_str(), std::ios::out);
	if (!new_file)
	{
		std::cerr << "The output file could not be opened" << std::endl;
		return 1;
	}
	while (getline(old_file, line)) 
	{
		int	last = 0;
		while ((find_value = line.find(s1, last)) != std::string::npos)
		{
			tmp = line.substr(find_value + s1.size());
			line.erase(find_value);
			line += s2 + tmp;
			last = find_value + s2.size();
		}
		new_file << line;
		if (!old_file.eof())
			new_file << std::endl;
	}
	old_file.close();
	new_file.close();
	return 0;
}
