#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <cstdint>
# include <iostream>
# include <stdint.h>
# include "Data.hpp"

class Serializer
{
private:
	Serializer();	
public:
	Serializer(const Serializer &serializer); 
	~Serializer();
	Serializer &operator=(const Serializer &serializer);

	static uintptr_t	serialize(Data *ptr);
	static Data*		deserialize(uintptr_t raw);
};

#endif