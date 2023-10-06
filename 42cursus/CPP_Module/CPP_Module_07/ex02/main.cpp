#include <iostream>
#include <string>

#include <Array.hpp>

#define MAX_VAL 10
int main(int, char**)
{
	Array<std::string>* stringTest = new Array<std::string>(10);
	for (int i = 0; i < 10; i++)
		std::cout << "'" << (*stringTest)[i] << "'" << std::endl;
	(*stringTest)[2] = "test";
	(*stringTest)[3] = "di";
	(*stringTest)[4] = "prova";
	std::cout << "Post Modify" << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << "'" << (*stringTest)[i] << "'" << std::endl;
	delete stringTest;

	Array<std::string>* emptyTest = new Array<std::string>();
	std::cout << *emptyTest << std::endl;
	delete emptyTest;

	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];
	std::cout << "numbers - mirror" << std::endl;
	for (int i = 0; i < MAX_VAL; i++)
		std::cout << numbers[i] << " - " << mirror[i] << std::endl;

	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand() % 100;
		numbers[i] = value;
		mirror[i] = value;
	}
	std::cout << "numbers - mirror" << std::endl;
	for (int i = 0; i < MAX_VAL; i++)
		std::cout << numbers[i] << " - " << mirror[i] << std::endl;
	//SCOPE
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
		std::cout << "tmp - test" << std::endl;
		for (int i = 0; i < MAX_VAL; i++)
			std::cout << tmp[i] << " - " << test[i] << std::endl;
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL - 1] = 42;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "something changed!! (" << mirror[i] << "->" << numbers[i] << ")" << std::endl;
		}
	}
	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand() % 100;
	}
	std::cout << "numbers(2) with operator <<:" << std::endl;
	std::cout << numbers << std::endl;
	delete [] mirror;
	return 0;
}