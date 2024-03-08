#ifndef PARSER_HPP
# define PARSER_HPP

#include "Server.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <cstring>  // strlen
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iterator>

class Parser {
private:
    std::vector<Server> _serverVect;
    mutable size_t _currentServer;   //Static variable to keep track of the current state index
    mutable size_t _tmpServer;        //Used with currentServer
    std::string	const _configFile;
    Parser();
    std::string	validConf(std::string file);

public:
    Parser(std::string absConfigPath);
    Parser(const Parser &parser);
    ~Parser();
    Parser &operator=(const Parser &parser);

    std::vector<Server> getServerVector();
    const Server* getServer();
    std::string	getConfigFile() const;

    class ConfigFileException : public std::exception {
        private:
            static const char* message;
        public:
            ConfigFileException() {}

            virtual const char* what() const throw();	// Overriding the what() method to provide an error message
    };
};

std::ostream & operator << (std::ostream &stream, Parser &parser);

#endif