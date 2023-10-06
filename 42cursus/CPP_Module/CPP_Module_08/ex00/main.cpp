#include <easyfind.hpp>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Insert only one number to find." << std::endl;
		std::cout << argv[0] << " <num>" << std::endl;
		return 1;
	}
	int arr[] = {1, -2, -3, 4, 5, 42, 6, -7, 8, -9, -10};
	std::vector<int> vect(arr, arr + sizeof(arr) / sizeof(int));
	std::list<int> list(arr, arr + sizeof(arr) / sizeof(int));

	std::cout << std::atoi(argv[1]) << std::endl;
	std::cout << easyFind(vect, std::atoi(argv[1])) << std::endl;
	std::cout << easyFind(list, std::atoi(argv[1])) << std::endl;
	return 0;
}