#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>
#include <iostream>
// #include "Array.tpp"	//the implementation of template class can be put in another file, that works as another hpp/cpp file called tpp

//'template' keyword is used to define a generic pattern thet the compiler can use to generate specific version of the functions or class for different data types
template<typename T>	//T is used as a placeholder for the actual data type that will be used when the function is invoked
class Array
{
private:
	T*	head;
	unsigned int	lenght;
public:
	Array();
	Array(unsigned int n);
	Array(const Array& array);
	~Array();
	Array &operator=(const Array &array);

	T& operator [] (unsigned int index) const;
	unsigned int size() const;

	class OutOfRange : public std::exception {
		private:
			static const char* message;
		public:
			OutOfRange() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

template<typename T>
std::ostream	&operator << (std::ostream &stream, Array<T>& array)
{
	for (size_t i = 0; i < array.size(); ++i)
		stream << array[i] << "->";
	stream << "NULL";
	return (stream);
}

//Constructors
template<typename T>
Array<T>::Array()
{
	this->lenght = 0;
	this->head = new T[this->lenght];
	std::cout << "Constructor called(Array)" << std::endl;
}

template<typename T>
Array<T>::Array(unsigned int n)
{
	this->lenght = n;
	this->head = new T[this->lenght];
	for (unsigned int i = 0; i < this->lenght; i++)
		this->head[i] = T();		//use the empty constructor of the template class
	std::cout << "Constructor called(Array)" << std::endl;
}

template<typename T>
Array<T>::Array(const Array &array)
{
	this->lenght = array.size();
	this->head = new T[this->lenght];
	for (unsigned int i = 0; i < this->lenght; i++)
		this->head[i] = array[i];
}

template<typename T>
Array<T> &Array<T>::operator = (const Array &array)
{
	delete[] this->head;	//have to delete if there are previous elements, before reallocating
	this->lenght = array.size();
	this->head = new T[this->lenght];
	for (unsigned int i = 0; i < this->lenght; i++)
		this->head[i] = array[i];
	return *this;
}

//Destructor
template<typename T>
Array<T>::~Array()
{
	delete[] this->head;
	std::cout << "Destructor called(Array)" << std::endl;
}

//Setters

//Getters
template<typename T>
T& Array<T>::operator [] (unsigned int index) const
{
	if (index >= this->lenght || index < 0)
		throw OutOfRange();
	return this->head[index];
}

template<typename T>
unsigned int Array<T>::size() const	//'const' keywork at the end means that the function doesn't modify the current instance of the class
{
	return this->lenght;
}

template<typename T>
const char* Array<T>::OutOfRange::message = "Index is out of scope.";
template<typename T>
const char * Array<T>::OutOfRange::what() const throw() 
{
	return this->message;
}

#endif
