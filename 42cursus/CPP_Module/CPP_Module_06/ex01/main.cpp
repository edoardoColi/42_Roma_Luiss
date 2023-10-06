/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/02 18:51:06 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

/*
*/
int main(int argc, char *argv[]) 
{
	Data* data;
	uintptr_t rawData;
	Data* retData;

	data = new Data;
	data->n = 42;

	std::cout << "Data             : " << data << "("<< data->n << ")"<< std::endl;
	rawData = Serializer::serialize(data);
	std::cout << "Raw data         : " << rawData << std::endl;
	retData = Serializer::deserialize(rawData);
	std::cout << "Deserialized data: " << retData << std::endl;
	std::cout << (data == retData) << std::endl;

	delete data;
	return 0;
}