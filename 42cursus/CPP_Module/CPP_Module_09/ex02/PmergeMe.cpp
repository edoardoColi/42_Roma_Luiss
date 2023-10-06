/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/08/29 16:32:13 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//Functions
/*
*/
template<typename T>	//T is used as a placeholdet for the actual data type that will be used when the function is invoked
static T recursiveFordJhonSort(const T& containerX)
{
	int n = containerX.size();
	if (n <= 1)		//if T has 0 or 1 element, it's already sorted.
		return containerX;

	// Step 1 & 2: Pair up elements and perform comparisons to determine the larger of the pairs
	T bigger_set;
	T unpaired_set;
	for (int i = 0; i < n; i += 2)
	{
		if (i + 1 < n)
		{
			if (containerX[i] < containerX[i+1])
			{
				bigger_set.push_back(containerX[i+1]);
				unpaired_set.push_back(containerX[i]);
			} else {
				bigger_set.push_back(containerX[i]);
				unpaired_set.push_back(containerX[i+1]);
			}
		} else {		//if there's an odd number of elements, leave one unpaired
			unpaired_set.push_back(containerX[i]);
		}
	}
	// Step 3: Recursively sort the larger elements
	bigger_set = recursiveFordJhonSort(bigger_set);
	// Step 4: Insert the first unpaired element that was paired with the first and smallest element of bigger_set
	int smallestNum = *std::min_element(bigger_set.begin(), bigger_set.end());
	for (int i = 0; i < n; i += 2)
	{
		if (i + 1 < n && containerX[i] < containerX[i+1])
		{
			if(containerX[i+1] == smallestNum)
			{
				bigger_set.insert(bigger_set.begin(), containerX[i]);
				auto it = std::find(unpaired_set.begin(), unpaired_set.end(), containerX[i]);
				if (it != unpaired_set.end())
					unpaired_set.erase(it); //having inserted befor I can now remove it to not have additional numbers
				break;
			}
		} else if  (i + 1 < n && containerX[i] >= containerX[i+1])
		{
			if(containerX[i] == smallestNum)
			{
				bigger_set.insert(bigger_set.begin(), containerX[i+1]);
				auto it = std::find(unpaired_set.begin(), unpaired_set.end(), containerX[i+1]);
				if (it != unpaired_set.end())
					unpaired_set.erase(it); //having inserted befor I can now remove it to not have additional numbers
				break;
			}
		}
	}
	// Step 5: Insert the remaining unpaired elements using binary search
	for (size_t i = 0; i < unpaired_set.size(); i++)
	{
		auto it = std::lower_bound(bigger_set.begin(), bigger_set.end(), unpaired_set[i]);	//find the position to insert using binary search
		bigger_set.insert(it, unpaired_set[i]);
	}
	return bigger_set;
}

/*
*/
void PmergeMe::sortVectorAlgorithm()
{
	if (this->container1.size() == 0)
		throw GeneralException();
	if (1)		//use my own Ford–Johnson algorithm (Merge-insertion sort)
		this->container1 = recursiveFordJhonSort(this->container1);
	else
		std::sort(this->container1.begin(), this->container1.end());	//the library function that is in algorithms
	return;
}

/*
*/
void PmergeMe::sortDequeAlgorithm()
{
	if (this->container2.size() == 0)
		throw GeneralException();
	if (1)		//use my own Ford–Johnson algorithm (Merge-insertion sort)
		this->container2 = recursiveFordJhonSort(this->container2);
	else
		std::sort(this->container2.begin(), this->container2.end());	//the library function that is in algorithms
	return;
}

//Constructors
PmergeMe::PmergeMe()
: sequence("")
{
	// std::cout << "Constructor called(PmergeMe)" << std::endl;
}

PmergeMe::PmergeMe(const std::string sequence)
: sequence(sequence)
{
	std::istringstream iss(this->sequence);  // Create a string stream from the input string
	
	int num;
	while (iss >> num) {
		this->container1.push_back(num);
		this->container2.push_back(num);
	}
	// std::cout << "Constructor called(PmergeMe)" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &pmergeMe)
{
	this->container1 = pmergeMe.container1;
	this->container2 = pmergeMe.container2;
	return;
}

PmergeMe	&PmergeMe::operator = (const PmergeMe &pmergeMe)
{
	this->~PmergeMe();
	::new(this) PmergeMe(pmergeMe);
	return (*this);
}

//Destructor
PmergeMe::~PmergeMe()
{
	// std::cout << "Destructor called(PmergeMe)" << std::endl;
}

//Setters

//Getters
std::string PmergeMe::getElementsCt1()
{
	std::string str;
	
	for (int num : this->container1)
		str += std::to_string(num) + " ";
	return str;
}

std::string PmergeMe::getElementsCt2()
{
	std::string str;
	
	for (int num : this->container2)
		str += std::to_string(num) + " ";
	return str;
}

//Exceptions
const char* PmergeMe::GeneralException::message = "Something happened... something that cannot be ignored.";
const char * PmergeMe::GeneralException::what() const throw()
{
	return this->message;
}
