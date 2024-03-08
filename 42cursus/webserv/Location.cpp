#include "Location.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, const Location &location) {
    const std::map<int, std::string>& map = location.getRedirectPageMap();

    stream << \
    "      Location:   " << location.getLocation() << std::endl << \
    "                  " << location.getRoot() << " (root)" << std::endl << \
    "                  " << location.getIndex() << " (index)" << std::endl << \
    "                  " << location.getAutoindex() << " (autoindex)" << std::endl << \
    "                  " << location.getMethods() << " (allowMethods)" << std::endl << \
    "                  " << location.getReturn() << " (return)" << std::endl << \
    "                  " << location.getTryFiles() << " (tryFiles)" << std::endl << \
    "                  " << location.getCgiPath() << " (cgiPath)" << std::endl << \
    "                  " << location.getCgiExt() << " (cgiExtension)" << std::endl;
    for (std::map<int, std::string>::const_iterator it = map.begin(); it != map.end(); ++it)
    {
        stream << \
    "                  " << it->first << " handled by " << it->second << "(redirection)" << std::endl;
    }

    return (stream);
}

void Location::setRedirects(const std::string& redirects) {
    std::istringstream iss(redirects);
    int key;
    std::string value;
    while (iss >> key >> value)
        this->_redirect[key] = value;
}

//Constructors
Location::Location(const Location &loc)    //TODO dovrei controllare funzionino, pero non si usano (in caso commente)
:_allowMethods(loc._allowMethods),_index(loc._index),_redirect(loc._redirect), _location(loc._location),_root(loc._root),_autoindex(loc._autoindex),_return(loc._return),_try_files(loc._try_files),_cgi_path(loc._cgi_path),_cgi_ext(loc._cgi_ext)
{
}

Location::Location(std::string location, std::string root, bool autoindex,std::string returnStr, std::string tryFiles, std::string cgiPath, std::string cgiExt,std::string redirects,std::string indice, std::string methods)
:_location(location), _root(root), _autoindex(autoindex), _return(returnStr), _try_files(tryFiles), _cgi_path(cgiPath), _cgi_ext(cgiExt),_index(indice),_allowMethods(methods)
{
    this->setRedirects(redirects);
    //TODO qui controllo i valori di inizzializzazione e lancio eccezzione se non bene
}

Location	&Location::operator = (const Location &location) {    //TODO dovrei controllare funzionino, pero non si usano (in caso commente)
    this->~Location();
    ::new(this) Location(location);
    return (*this);
}

//Destructor
Location::~Location() {
    // std::cout << "Destructor called(Location)" << std::endl;
}

//Setters

//Getters
std::string	Location::getLocation() const
{
    return this->_location;
}

std::string	Location::getRoot() const
{
    return this->_root;
}

std::string	Location::getIndex() const
{
    return this->_index;
}

std::string	Location::getMethods() const
{
    return this->_allowMethods;
}

bool Location::getAutoindex() const
{
    return _autoindex;
}

std::string	Location::getReturn() const
{
    return this->_return;
}

std::string	Location::getTryFiles() const
{
    return this->_try_files;
}

std::string	Location::getCgiPath() const
{
    return this->_cgi_path;
}

std::string	Location::getCgiExt() const
{
    return this->_cgi_ext;
}

const std::map<int, std::string>& Location::getRedirectPageMap() const
{
    return _redirect;
}

/*
Ritorna una stringa vuota se non c'e il codice di errore(code)
*/
std::string	Location::getRedirectPage(int code) const
{
    std::map<int, std::string>::const_iterator it = _redirect.find(code);
    if (it != _redirect.end())
        return it->second;
    else
        return "";
}

//Exceptions
const char* Location::LocationBlockException::message = "The location block is invalid, as template see NGINX server block configuration.";
const char * Location::LocationBlockException::what() const throw() {
    return this->message;
}
