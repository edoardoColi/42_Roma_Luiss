#include "Parser.hpp"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
    std::string buffer;
    if (file) {
        file.seekg(0, std::ios::end);
        buffer.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&buffer[0], buffer.size());
        file.close();
    }
    return buffer;
}

/*
*/
int handleConnection(int clientSocket, int bfsz) {
    char bufferRead[bfsz];
    bzero(bufferRead, bfsz);

    // Read the client's request
    ssize_t bytesRead = recv(clientSocket, bufferRead, sizeof(bufferRead) - 1, 0);
    if (bytesRead <= 0) {
        std::cerr << "Error: recv from clientSocket, closing clientSocket" << std::endl;
        close(clientSocket);
        return -1;
    }

    // Print the client's request
    std::cout << "Received request from client:\n" << bufferRead << std::endl;

    // Respond with the static page
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: ";
    std::string body = "<html><body><h1>Hello, this is a static page by &#9733;ecoli&#9733; !!!</h1></body></html>";
    response += std::to_string(body.length()) + "\r\nContent-Type: text/html\r\n\r\n" + body;

    send(clientSocket, response.c_str(), response.length(), 0);
    // Don't close the client socket here if you want to keep it open for future communication
    // close(clientSocket);
    return 0;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments, expecting only one config file" << std::endl;
        return 1;
    }
    if ((std::string(argv[1]).substr(std::string(argv[1]).find_last_of(".") + 1) != "conf"))
    {
        std::cout << "Invalid config file, exiting" << std::endl;
        return 1;
    }
    Parser Parsy = Parser(argv[1]);

    const Server* server;
    while ((server = Parsy.getServer()) != NULL)
    {
        std::cout << *server << std::endl;
    }

    std::vector<Server> Servers;
    Servers = Parsy.getServerVector();
    while (1) 
    {
        fd_set read, write, active;
        FD_ZERO(&active);

        for (size_t i = 0; i < Servers.size(); i++) {
            FD_SET(Servers[i].getSocket(), &active);
        }

        // Initialize read and write sets
        read = active;
        FD_ZERO(&write);

        if (select(FD_SETSIZE, &read, &write, NULL, NULL) < 0) {
    		std::cerr << "Error: select: Bad file descriptor" << std::endl;
            break;
        }

        for (size_t i = 0; i < Servers.size(); i++) {
            if (FD_ISSET(Servers[i].getSocket(), &read)) {
                int client_socket = accept(Servers[i].getSocket(), NULL, NULL); // Accept new connection
                if (client_socket < 0) {
            		std::cerr << "Error: accept: Bad file descriptor | Interrupted system call | Too many open files" << std::endl;
                    exit(1);
                }
                Servers[i]._cSockets.push_back(client_socket);  // Store the client socket
                if (handleConnection(client_socket,Servers[i].getMaxBodySize()) == -1) {
                    auto it = std::find(Servers[i]._cSockets.begin(), Servers[i]._cSockets.end(), client_socket);  //Remove the closed client socket from the vector
                    if (it != Servers[i]._cSockets.end()) {
                        Servers[i]._cSockets.erase(it);
                    }
                }
            }
        }
    }

    while ((server = Parsy.getServer()) != NULL)    //Clean up server sockets
    {
        close((*server).getSocket());
    }

    return 0;
}