#ifndef LOCATION_HPP
# define LOCATION_HPP

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

class Location {
private:
    std::string	const _location;
    std::string const _root;
    std::string const _index;
    bool const _autoindex;
    std::string _allowMethods;
    std::map <int,std::string> _redirect;
    std::string const _return;
    std::string const _try_files;
    std::string const _cgi_path;
    std::string const _cgi_ext;
    Location();
    void setRedirects(const std::string& redirects);

public:
    Location(std::string location, std::string root, bool autoindex, std::string returnStr, std::string tryFiles, std::string cgiPath, std::string cgiExt,std::string redirects,std::string indice, std::string methods);
    Location(const Location &loc);
    ~Location();
    Location &operator=(const Location &location);

    std::string	getLocation() const;
    std::string	getRoot() const;
    std::string	getIndex() const;
    std::string	getMethods() const;
    bool getAutoindex() const;
    std::string	getReturn() const;
    std::string	getTryFiles() const;
    std::string	getCgiPath() const;
    std::string	getCgiExt() const;
    const std::map<int, std::string>& getRedirectPageMap() const;
    std::string	getRedirectPage(int code) const;

    class LocationBlockException : public std::exception {
        private:
            static const char* message;
        public:
            LocationBlockException() {}

            virtual const char* what() const throw();	// Overriding the what() method to provide an error message
    };
};

std::ostream & operator << (std::ostream &stream, const Location &location);

#endif