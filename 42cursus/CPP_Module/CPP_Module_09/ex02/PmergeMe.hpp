#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <exception>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <deque>
class PmergeMe
{
private:
	std::string const sequence;
	std::vector<int> container1;	//A standard container which offers fixed time access to individual elements in any order.
	std::deque<int> container2;	//A standard container using fixed-size memory allocation and constant-time manipulation of elements at either ends.

public:
	PmergeMe();
	PmergeMe(const std::string sequence);
	PmergeMe(const PmergeMe &pmergeMe);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &pmergeMe);

	std::string getElementsCt1();
	std::string getElementsCt2();

	void sortVectorAlgorithm();
	void sortDequeAlgorithm();

	class GeneralException : public std::exception {
		private:
			static const char* message;
		public:
			GeneralException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

#endif
