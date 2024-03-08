#ifndef SERVER_HPP
# define SERVER_HPP

#include "Location.hpp"

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
#include <sys/select.h> // select()
#include <sys/socket.h> //socket(), bind(), listen(), connect(), getsockname(), accept(), send(), struct sockaddr_in
#include <netdb.h> //getprotobyname()
#include <sys/types.h>
#include <arpa/inet.h> //ntohl() etc
#include <dirent.h> // readdir(), opendir(), closedir()
#include <unistd.h> //execve(), dup(), dup2(),
#include <signal.h>// 
#include <fcntl.h>

class Server {
private:
    std::string	const _serverName;
    std::string const _host;
    int	const _listen;
    std::string const _root;
    int const _client_max_body_size;
    std::string const _index;
    std::map <int,std::string> _errorPage;
    std::vector<Location> _locationVect;
    mutable size_t _currentLocation;
    mutable size_t _tmpLocation;        //Used with currentLocation
    struct sockaddr_in _addr;
    int _serverSocket;

    Server();
    void setErrors(const std::string& errorPatterns);
    void setLocations(const std::string& locationPatterns);

public:

    std::vector<int> _cSockets;  // Store client sockets

    Server(std::string name, std::string host, int listen, std::string root, int bodySize, std::string index, std::string errors, std::string locations);
    Server(const Server &server);
    ~Server();
    Server &operator=(const Server &server);

    void run();
    int start();
    void printInfo();
    const Location* getLocation() const;
    std::string	getServerName() const;
    std::string	getHost() const;
    int	getListen() const;
    std::string	getRoot() const;
    int getMaxBodySize() const;
    std::string getIndex() const;
    const std::map<int, std::string>& getErrorPageMap() const;
    std::string	getErrorPage(int code) const;
    void setSocket(int n);
    int	getSocket() const;

    class ServerBlockException : public std::exception {
        private:
            static const char* message;
        public:
            ServerBlockException() {}

            virtual const char* what() const throw();	// Overriding the what() method to provide an error message
    };
        class ServerSocketException : public std::exception {
        private:
            static const char* message;
        public:
            ServerSocketException() {}

            virtual const char* what() const throw();	// Overriding the what() method to provide an error message
    };
};

std::ostream & operator << (std::ostream &stream, const Server &server);

#endif