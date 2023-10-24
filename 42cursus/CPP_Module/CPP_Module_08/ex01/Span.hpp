#ifndef SPAN_HPP
# define SPAN_HPP

# include <exception>
# include <iostream>
# include <algorithm>
# include <list>
# include <vector>

class Span
{
private:
	unsigned int	n;
	std::list<unsigned int>	head;
public:
	Span();
	Span(unsigned int n);
	Span(const Span &Span);
	~Span();
	Span &operator=(const Span &Span);

	void	addNumber(unsigned int n);
	Span	addRandom(unsigned int n);
	int		shortestSpan();
	int		longestSpan();
	void	debugListing();

	class SpanIsFullException : public std::exception {
		private:
			static const char* message;
		public:
			SpanIsFullException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
	class SizeTooSmallException : public std::exception {
		private:
			static const char* message;
		public:
			SizeTooSmallException() {}

			virtual const char* what() const throw();	// Overriding the what() method to provide an error message
	};
};

#endif
