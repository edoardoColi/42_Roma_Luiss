#include "Server.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, const Server &server) {
    if (0) {
        const std::map<int, std::string>& map = server.getErrorPageMap();
        stream << \
        "Server Name: " << server.getServerName() << std::endl << \
        "   Hostname: " << server.getHost() << std::endl << \
        "       Port: " << server.getListen() << std::endl << \
        "       Root: " << server.getRoot() << std::endl << \
        "  MaxBodySz: " << server.getMaxBodySize() << std::endl << \
        "      Index: " << server.getIndex() << std::endl << \
        " ServerSock: " << server.getSocket() << std::endl;
        for (std::map<int, std::string>::const_iterator it = map.begin(); it != map.end(); ++it)
        {
            stream << \
        " Error Code: " << it->first << " handled by " << it->second << std::endl;
        }
        const Location* location;
        while ((location = server.getLocation()) != NULL)
        {
            stream << *location << std::endl;
        }
        stream << "\033[38;5;51m================================================================\033[0m"<< std::endl;
        stream << "Server name: "<< server.getServerName() << ", listening on port "<< server.getListen() << std::endl;
        stream << "domain: "<< AF_INET << "| type: " << SOCK_STREAM << "| protocol:" << 0 << std::endl;
        stream << "\033[38;5;51m================================================================\033[0m"<< std::endl;
    } else {
        stream << "\033[38;5;51m================================================================\033[0m"<< std::endl;
        stream << "Server name: "<< server.getServerName() << ", listening on port "<< server.getListen() << std::endl;
        stream << "\033[38;5;51m================================================================\033[0m"<< std::endl;
    }
    return (stream);
}

void Server::setErrors(const std::string& errorPatterns) {
    std::istringstream iss(errorPatterns);
    int key;
    std::string value;
    while (iss >> key >> value)
        this->_errorPage[key] = value;
}

/*
Leva tutti gli white space da inizio e fine stringa
*/
std::string trim2(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    size_t last = str.find_last_not_of(" \t\n\r\f\v");

    if (first == std::string::npos || last == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

std::string locationMatch(const std::string& input, size_t& startPos, size_t& baseServer) {
    size_t startBrace = input.find("location", startPos);
    size_t openingBrace   = input.find("{", startPos);
    size_t closingBrace = input.find('}', openingBrace);
    size_t nesting = 0;
    while (startBrace != std::string::npos && openingBrace != std::string::npos && closingBrace != std::string::npos)
    {
        baseServer = (baseServer == 0) ? 1 : baseServer;
        size_t nestedOpening = input.find('{', openingBrace + 1);
        if (nestedOpening != std::string::npos && nestedOpening < closingBrace)
        {
            nesting = (nesting == 0) ? 1 : nesting;
            openingBrace = nestedOpening;
            closingBrace = input.find('}', nestedOpening);
        } else {
            size_t consecutiveOpening = input.find('{', closingBrace);
            size_t nextServBlock = input.find("server {", closingBrace);
            size_t tmpClosingBrace = input.find('}', closingBrace + 1);
            if (nesting == 1 && consecutiveOpening != std::string::npos && consecutiveOpening < tmpClosingBrace && consecutiveOpening < nextServBlock)
            {
                openingBrace = consecutiveOpening;
                closingBrace = input.find('}', consecutiveOpening);
            } else {
                startPos = closingBrace + 1;
                if (nesting==0 || tmpClosingBrace > nextServBlock || tmpClosingBrace == std::string::npos)
                {
                    tmpClosingBrace = closingBrace;
                }
                size_t da=startBrace + 8;
                size_t per=tmpClosingBrace - startBrace - 8;
                return trim2(input.substr(startBrace + 8, tmpClosingBrace - startBrace - 8));
            }
        }
    }
    if (!baseServer)
    {
        throw Server::ServerBlockException();   //Never occurr because is checked in Parser
    }
    return "";
}

/*
Estrae la prima parola della stringa del blocco location
*/
std::string retrieveEndpoint(std::string input) {
    std::string result;
    for (size_t i = 0; i < input.length(); ++i)
    {
        if (std::isspace(input[i]))
            continue;
        while (i < input.length() && !std::isspace(input[i]) && input[i] != ';')
        {
            result += input[i];
            ++i;
        }
        break;
    }
    return result;
}

/*
Recupera il primo root e assegna tutto quello scritto come root (spazi compresi) fino ;
*/
std::string retrieveRoot2(std::string input) {
    size_t lastServerNamePos = input.find("root");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("root");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo index e assegna tutto quello scritto come index (spazi compresi) fino ;
*/
std::string retrieveIndex2(std::string input) {
    size_t lastServerNamePos = input.find("\nindex");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen(" index");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo return e assegna tutto quello scritto come stringa (spazi compresi) fino ;
*/
std::string retrieveReturns(std::string input) {
    size_t lastServerNamePos = input.find("return");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("return");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo allow_methods e assegna tutto quello scritto come stringa (spazi compresi) fino ;
*/
std::string retrieveMethods(std::string input) {
    size_t lastServerNamePos = input.find("allow_methods");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("allow_methods");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo try_files e assegna tutto quello scritto come try_files (spazi compresi) fino ;
*/
std::string retrieveTryFiles(std::string input) {
    size_t lastServerNamePos = input.find("try_files");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("try_files");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo cgi_path e assegna tutto quello scritto come cgi_path (spazi compresi) fino ;
*/
std::string retrieveCgiPath(std::string input) {
    size_t lastServerNamePos = input.find("cgi_path");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("cgi_path");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo cgi_ext e assegna tutto quello scritto come cgi_ext (spazi compresi) fino ;
*/
std::string retrieveCgiExt(std::string input) {
    size_t lastServerNamePos = input.find("cgi_ext");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("cgi_ext");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim2(extractedWord);
}

/*
Recupera il primo autoindex e assegna tutto quello scritto come variabile (spazi compresi) fino ;
se esattamente "on" mette true altrimenti false di default (scrivere esplicitamente "off" praticamente inutile)
*/
bool retrieveAutoindex(std::string input) {
    size_t lastServerNamePos = input.find("autoindex");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("autoindex");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return (trim2(extractedWord) == "on");
}

/*
Recupera concatenando i dettagli delle redirect per farle parsare al location 
*/
std::string retrieveRedirects(std::string input) {
    std::string concatenatedRed;

    size_t pos = input.find("redirect");
    while (pos != std::string::npos) {
        pos += 8;      //Move at the end of "redirect"
        size_t semicolonPos = input.find(";", pos);
        if (semicolonPos != std::string::npos) {
            concatenatedRed += trim2(input.substr(pos, semicolonPos - pos)) + " ";
            pos = input.find("redirect", semicolonPos);
        } else {
            break;      //No more error_page specifications
        }
    }
    return concatenatedRed;
}

void Server::setLocations(const std::string& locationPatterns) {
    size_t startPos = 0;
    size_t baseLocation = 0;
    std::string locationBlock;
    while ((locationBlock = locationMatch(locationPatterns, startPos, baseLocation)) != "")
    {
        std::string argv1 = retrieveEndpoint(locationBlock);
        std::string argv2 = retrieveRoot2(locationBlock);
        bool argv3 = retrieveAutoindex(locationBlock);
        std::string argv4 = retrieveReturns(locationBlock);
        std::string argv5 = retrieveTryFiles(locationBlock);
        std::string argv6 = retrieveCgiPath(locationBlock);
        std::string argv7 = retrieveCgiExt(locationBlock);
        std::string argv8 = retrieveRedirects(locationBlock);
        std::string argv9 = retrieveIndex2(locationBlock);
        std::string argv10 = retrieveMethods(locationBlock);

        _locationVect.push_back(Location(argv1,argv2,argv3,argv4,argv5,argv6,argv7,argv8,argv9,argv10));
    }
}

int Server::start() {
    int ssocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ssocket == -1) {
		std::cerr << "Error creating server Socket" << std::endl;
        throw Server::ServerBlockException();
    }

    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);     //Use this if your server is intended to only accept connections from clients running on the same machine
    // _addr.sin_addr.s_addr = INADDR_ANY;        //Use this if you want your server to be accessible from any network interface
    _addr.sin_port = htons(_listen);

    int reuseSize = 1;
	if (setsockopt(ssocket, SOL_SOCKET, SO_REUSEADDR, &reuseSize, sizeof(reuseSize)) == -1) {        //Used to set options on a socket. Common options include controlling socket behavior, such as enabling socket reuse (SO_REUSEADDR) or setting a timeout
		std::cerr << "Error: Socket could not be setsockopt" << std::endl;
        close(ssocket);
        throw Server::ServerSocketException();
    }
	if (fcntl(ssocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC) == -1) {    //Used for more advanced socket operations, such as setting the socket to non-blocking mode
		std::cerr << "Error modifying socket flags" << std::endl;
        close(ssocket);
        throw Server::ServerSocketException();
    }
    if (bind(ssocket, reinterpret_cast<struct sockaddr*>(&_addr), sizeof(_addr)) == -1) {
		std::cerr << "Unable to bind socket" << std::endl;
        close(ssocket);
        throw Server::ServerSocketException();
    }
    int backlog = 5;                                //Setting the backlog to 1 means that the server will be able to handle one pending connection at a time
    if (listen(ssocket, backlog) == -1) {      //SOMAXCONN is a constant representing the maximum length that the queue of pending connections 
		std::cerr << "Too many pending connections" << std::endl;
        close(ssocket);
        throw Server::ServerSocketException();
    }
    return ssocket;
}

// void Server::run() {
// 	fd_set read, write, active;
// 	struct timeval time;
// 	// while (1)
// 	// {
// 	// 	for (int k = 0; k < Parsy.checkConf(conFile); k++)
// 	// 	{
// 	// 		FD_ZERO(&active);
// 	// 		FD_SET();
// 	// 	}
// 	// }
// }

//Constructors
Server::Server(const Server &server)    //TODO dovrei controllare funzionino, pero non si usano (in caso commente)
:_addr(server._addr),_serverSocket(server._serverSocket),_errorPage(server._errorPage),_locationVect(server._locationVect),_currentLocation(server._currentLocation),_tmpLocation(server._tmpLocation),_serverName(server._serverName),_host(server._host),_listen(server._listen),_root(server._root),_client_max_body_size(server._client_max_body_size),_index(server._index)
{
    this->_currentLocation = 0;
    this->_tmpLocation = 0;
}

Server::Server(std::string name, std::string host, int listen, std::string root, int bodySize, std::string index, std::string errors, std::string locations)
:_currentLocation(0), _tmpLocation(0), _serverName(name), _host(host), _listen(listen), _root(root), _client_max_body_size(bodySize), _index(index)
{
    this->setErrors(errors);
    this->setLocations(locations);
    this->setSocket(this->start());
    //TODO qui controllo i valori di inizzializzazione e lancio eccezzione se non bene
}

Server	&Server::operator = (const Server &server) {    //TODO dovrei controllare funzionino, pero non si usano (in caso commente)
    this->~Server();
    ::new(this) Server(server);
    return (*this);
}

//Destructor
Server::~Server() {
    // std::cout << "Destructor called(Server)" << std::endl;
}

//Setters

//Getters

void Server::setSocket(int n) {
    this->_serverSocket = n;
}

int	Server::getSocket() const
{
    return this->_serverSocket;
}

const Location* Server::getLocation() const
{
    if (_locationVect.empty() || _tmpLocation == 1) {
        _tmpLocation = 0;
        return NULL;
    }
    const Location* tmpLocation = &_locationVect[_currentLocation];
    _currentLocation = (_currentLocation + 1) % _locationVect.size();  // Move to the next state, loop back if necessary
    if (_currentLocation == 0)
        _tmpLocation = 1;
    return tmpLocation;
}

std::string	Server::getServerName() const
{
    return this->_serverName;
}

std::string	Server::getHost() const
{
    return this->_host;
}

int	Server::getListen() const
{
    return this->_listen;
}

std::string	Server::getRoot() const
{
    return this->_root;
}

int	Server::getMaxBodySize() const
{
    return this->_client_max_body_size;
}

std::string	Server::getIndex() const
{
    return this->_index;
}

const std::map<int, std::string>& Server::getErrorPageMap() const
{
    return _errorPage;
}

/*
Ritorna una stringa vuota se non c'e il codice di errore(code)
*/
std::string	Server::getErrorPage(int code) const
{
    std::map<int, std::string>::const_iterator it = _errorPage.find(code);
    if (it != _errorPage.end())
        return it->second;
    else
        return "";
}

//Exceptions
const char* Server::ServerBlockException::message = "The server block is invalid, as template see NGINX server block configuration.";
const char * Server::ServerBlockException::what() const throw() {
    return this->message;
}

const char* Server::ServerSocketException::message = "Something in the server socket funnction start() fails.";
const char * Server::ServerSocketException::what() const throw() {
    return this->message;
}
