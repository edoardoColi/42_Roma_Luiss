#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <exception>
# include <iostream>
# include <stack>
# include <deque>
# include <list>
// #include "MutantStack.tpp"	//the implementation of template class can be put in another file, that works as another hpp/cpp file called tpp

//'template' keyword is used to define a generic pattern thet the compiler can use to generate specific version of the functions or class for different data types
template<typename T>	//T is used as a placeholdet for the actual data type that will be used when the function is invoked
class MutantStack : public std::stack<T, std::deque<T>>
{
public:
	MutantStack();
	MutantStack(const MutantStack& MutantStack);
	~MutantStack();
	MutantStack &operator=(const MutantStack &MutantStack);

	typedef typename std::deque<T>::iterator iterator;
	iterator	begin();
	iterator	end();
};

//Functions
template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
	return this->c.end();
}


//Constructors
template<typename T>
MutantStack<T>::MutantStack()
{
	std::cout << "Constructor called(MutantStack)" << std::endl;
}

template<typename T>
MutantStack<T>::MutantStack(const MutantStack &mutantStack)
: std::stack<T>(mutantStack)
{
	return;
}

template<typename T>
MutantStack<T> &MutantStack<T>::operator = (const MutantStack &mutantStack)
{
	this->c = mutantStack.c;
	return *this;
}

//Destructor
template<typename T>
MutantStack<T>::~MutantStack()
{
	this->c.clear();
	std::cout << "Destructor called(MutantStack)" << std::endl;
}

//Setters

//Getters

#endif
