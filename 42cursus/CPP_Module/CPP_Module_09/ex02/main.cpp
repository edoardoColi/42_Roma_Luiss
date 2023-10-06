/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/08/29 16:56:25 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <chrono>

#include "PmergeMe.hpp"

/*
Can be used in the Bash like this: ./PmergeMe `shuf -i 1-100000 -n 42 | tr "\n" " "`
*/
int main(int argc, char* argv[])
{
	auto startTime = std::chrono::high_resolution_clock::now();
	std::string unsorted("");
	std::string sorted("");
	std::string result1("");
	std::string result2("");
	int quantity = argc;

	if (argc == 1)
	{
		std::cout << "The program takes as arguments a sequence of positive integers." << std::endl;
		std::cout << "Usage: " << argv[0] << " <int> ..." << std::endl;
		return 1;
	}
	for (int i = 1; i < argc; ++i) {
		for (char c : std::string(argv[i])){
			if (!std::isdigit(c))
			{
				std::cout << "Error: something is not a number, or just not positive." <<std::endl;
				return 1;
			}
		}
		if (std::string(argv[i]).empty())
			quantity--;
		else
			unsorted += std::string(argv[i]) + " ";
	}
	try
	{
		PmergeMe test(unsorted);

		auto startTime1 = std::chrono::high_resolution_clock::now();
		test.sortVectorAlgorithm();
		auto endTime1 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(endTime1 - startTime1);

		auto startTime2 = std::chrono::high_resolution_clock::now();
		test.sortDequeAlgorithm();
		auto endTime2 = std::chrono::high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - startTime2);

		result1 = test.getElementsCt1();
		result2 = test.getElementsCt2();

		if (result1 != result2)
			std::cout << "Error: sorting results appear to be different." <<std::endl;
		else
		{
		std::cout << std::setw(8) << std::left << "Before:" << unsorted << std::endl;
		std::cout << std::setw(8) << std::left << "After:" << result1 << std::endl;
		std::cout << "Time to process a range of " << quantity - 1 << " elements with std::vector<int> : " << duration1.count() << " microseconds" << std::endl;
		std::cout << "Time to process a range of " << quantity - 1 << " elements with std::deque<int>  : " << duration2.count() << " microseconds" << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	std::cout << "All execution process time : " << duration.count() << " microseconds" << std::endl;
	return 0;
}