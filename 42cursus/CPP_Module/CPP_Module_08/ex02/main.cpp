#include <MutantStack.hpp>

int main(int, char**)
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);
	std::cout << "New size after 2 push(): " << mstack.size() << std::endl;

	std::cout << "First elem of stack: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "New size after 1 pop(): " << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(42);
	mstack.push(0);
	std::cout << "New size after 5 push(): " << mstack.size() << std::endl;

	MutantStack<int>::iterator it = mstack.begin();

	++it;		//needed because if is used an iterator implemented by me this line checks the ++ and -- methods
	--it;
	while (it != mstack.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	std::stack<int> s(mstack);
	while (!s.empty()) {
		std::cout << s.top() << " "; // Print the top element of s
		s.pop(); // Pop the top element from s
	}
	std::cout << "(Reverse way because is pop from top: is an ordinary stack, can't use iterator here)" << std::endl;

	std::list<int> mlist;

	mlist.push_back(5);
	mlist.push_back(17);
	std::cout << "New size after 2 push_back(): " << mlist.size() << std::endl;

	std::cout << "First elem of list: " << mlist.front() << std::endl;		//not like the stack because the beginning is considered differently (inversely)
	mlist.pop_back();
	std::cout << "New size after 1 pop_back(): " << mlist.size() << std::endl;

	mlist.push_back(3);
	mlist.push_back(5);
	mlist.push_back(737);
	mlist.push_back(42);
	mlist.push_back(0);
	std::cout << "New size after 5 push_back(): " << mlist.size() << std::endl;

	for (const int& value : mlist) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	return 0;
}