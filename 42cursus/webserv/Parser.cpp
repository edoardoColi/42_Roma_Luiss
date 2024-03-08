#include "Parser.hpp"

//Functions
/*
*/
std::ostream	&operator << (std::ostream &stream, Parser &parser) {
    stream << "In configuration file \"" << parser.getConfigFile() << "\" we have:" << std::endl;
    const Server* server;
    while ((server = parser.getServer()) != NULL)
    {
        stream << "---- - -  -  - - ----" << std::endl << \
        *server << std::endl;
    }
    stream << "---- - -  -  - - ----";
    return (stream);
}

/*
Serve per contare che nel file di configurazione ci sia un numero pari di graffe
Non ci siano aperte prima di chiuse e tutte abbiano un corrispettivo
*/
bool hasBalancedBraces(const std::string& input) {
    std::stack<char> braceStack;

    for (std::size_t i = 0; i < input.length(); ++i)
    {
        if (input[i] == '{')
        {
            braceStack.push('{');
        } else if (input[i] == '}')
        {
            if (braceStack.empty())
            {
                return false;  // Unmatched closing brace without an open brace
            }
            braceStack.pop();
        }
    }
    return braceStack.empty();  // If the stack is empty, all braces are matched
}

/*
Leva le righe con i commenti(#)
*/
void removeCommentedLines(std::string& content) {
    std::istringstream iss(content);
    std::ostringstream oss;

    std::string line;
    while (std::getline(iss, line)) {
        // Remove leading whitespaces
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

        // Check if the line is not a comment
        if (!line.empty() && line[0] != '#') {
            oss << line << '\n';
        }
    }
    content = oss.str();
}

/*
Leva tutti gli white space da inizio e fine stringa
*/
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    size_t last = str.find_last_not_of(" \t\n\r\f\v");

    if (first == std::string::npos || last == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

/*
Lancia eccezioni se ci sono problemi con la struttura dei blocchi Server nel file di configurazione
Nested braces max depth 1 ({{}}) in config file
*/
std::string serverMatch(const std::string& input, size_t& startPos, size_t& baseServer) {
    size_t startBrace = input.find("server {", startPos);
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
                return trim(input.substr(startBrace + 8, tmpClosingBrace - startBrace - 8));
            }
        }
    }
    if (!baseServer)
    {
        throw Parser::ConfigFileException();
    }
    return "";
}

/*
Recupera il primo sarver_name e assegna tutto quello scritto come nome (spazi compresi) fino ;
Remove part of Location, additional parameters of server must be befor location block
*/
std::string retrieveName(std::string input) {
    size_t lastServerNamePos = input.find("server_name");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("server_name");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim(extractedWord);
}

/*
Recupera il primo host e assegna tutto quello scritto come ip (spazi compresi) fino ;
Remove part of Location, additional parameters of server must be befor location block
*/
std::string retrieveIp(std::string input) {
    size_t locationData = input.find("location");
    if (locationData != std::string::npos)
        input = input.substr(0, locationData);
    size_t lastServerNamePos = input.find("host");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("host");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim(extractedWord);
}

/*
Recupera il primo listen e assegna tutto quello scritto come porta (spazi compresi) fino ; e poi fa atoi()
Remove part of Location, additional parameters of server must be befor location block
*/
int retrievePort(std::string input) {
    size_t locationData = input.find("location");
    if (locationData != std::string::npos)
        input = input.substr(0, locationData);
    size_t lastServerNamePos = input.find("listen");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("listen");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    const char* port = (trim(extractedWord)).c_str();
    return std::atoi(port);
}

/*
Recupera il primo root e assegna tutto quello scritto come root (spazi compresi) fino ;
Remove part of Location, additional parameters of server must be befor location block
*/
std::string retrieveRoot(std::string input) {
    size_t locationData = input.find("location");
    if (locationData != std::string::npos)
        input = input.substr(0, locationData);

    size_t lastServerNamePos = input.find("root");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("root");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim(extractedWord);
}

/*
Recupera il primo client_max_body_size e assegna tutto quello scritto come variabile (spazi compresi) fino ;
Remove part of Location, additional parameters of server must be befor location block
*/
int retrieveBodySize(std::string input) {
    size_t locationData = input.find("location");
    if (locationData != std::string::npos)
        input = input.substr(0, locationData);
    size_t lastServerNamePos = input.find("client_max_body_size");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("client_max_body_size");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    if (extractedWord.empty())
        return 65536;
    const char* maxsize = (trim(extractedWord)).c_str();
    return std::atoi(maxsize);
}

/*
Recupera il primo index e assegna tutto quello scritto come variabile (spazi compresi) fino ;
Remove part of Location, additional parameters of server must be befor location block
*/
std::string retrieveIndex(std::string input) {
    size_t locationData = input.find("location");
    if (locationData != std::string::npos)
        input = input.substr(0, locationData);
    size_t lastServerNamePos = input.find("index");
    size_t nextSemicolonPos = input.find(";", lastServerNamePos);
    std::string extractedWord;
    if (lastServerNamePos != std::string::npos && nextSemicolonPos != std::string::npos) {
        size_t start = lastServerNamePos + std::strlen("index");
        size_t length = nextSemicolonPos - start;
        extractedWord = input.substr(start, length);
    }
    return trim(extractedWord);
}

/*
Recupera concatenando i dettagli delle error_page per farle parsare al server 
Remove part of Location, additional parameters of server must be befor location block
*/
std::string retrieveErrorP(std::string input) {
    size_t locationData = input.find("location");
    if (locationData != std::string::npos)
        input = input.substr(0, locationData);
    std::string concatenatedErrors;

    size_t pos = input.find("error_page");
    while (pos != std::string::npos) {
        pos += 10;      //Move at the end of "error_page"
        size_t semicolonPos = input.find(";", pos);
        if (semicolonPos != std::string::npos) {
            concatenatedErrors += trim(input.substr(pos, semicolonPos - pos)) + " ";
            pos = input.find("error_page", semicolonPos);
        } else {
            break;      //No more error_page specifications
        }
    }
    return concatenatedErrors;
}

/*
Recupera concatenando i dettagli delle location per farle parsare al server 
*/
std::string retrieveLocation(std::string input) {
    std::string concatenatedErrors;

    size_t pos = input.find("location");
    while (pos != std::string::npos) {
        size_t semicolonPos = input.find("}", pos);
        if (semicolonPos != std::string::npos) {
            concatenatedErrors += trim(input.substr(pos, semicolonPos - pos + 1)) + " ";
            pos = input.find("location", semicolonPos);
        } else {
            break;      //No more error_page specifications
        }
    }
    return concatenatedErrors;
}

/*
Lancia eccezioni se ci sono problemi con le keywork nel file di configurazione
*/
std::string	Parser::validConf(std::string file) {
    try{
        std::ifstream configFile(file.c_str());
        if (!configFile.is_open())
        {
            throw Parser::ConfigFileException();
        }
        std::string configContent((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());  //Read the entire file into a string
        removeCommentedLines(configContent);
        if (configContent.empty() || !hasBalancedBraces(configContent))
        {
            throw Parser::ConfigFileException();
        }

        size_t startPos = 0;
        size_t baseServer = 0;
        std::string serverBlock;
        while ((serverBlock = serverMatch(configContent, startPos, baseServer)) != "")
        {
            std::string argv1 = retrieveName(serverBlock);
            std::string argv2 = retrieveIp(serverBlock);
            int argv3 = retrievePort(serverBlock);
            std::string argv4 = retrieveRoot(serverBlock);
            int argv5 = retrieveBodySize(serverBlock);
            std::string argv6 = retrieveIndex(serverBlock);
            std::string argv7 = retrieveErrorP(serverBlock);
            std::string argv8 = retrieveLocation(serverBlock);
            _serverVect.push_back(Server(argv1,argv2,argv3,argv4,argv5,argv6,argv7,argv8));
        }
    } catch (const Parser::ConfigFileException& e) {
        throw;  //Catch and rethrow the same exception
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return file;
}

//Constructors
Parser::Parser(const Parser &parser)    //TODO dovrei controllare funzionino, pero non si usano (in caso commente)
:_serverVect(parser._serverVect),_currentServer(parser._currentServer),_tmpServer(parser._tmpServer),_configFile(parser._configFile)
{
    this->_currentServer = 0;
    this->_tmpServer = 0;
}

Parser::Parser(std::string absConfigPath)
:_currentServer(0), _tmpServer(0), _configFile(validConf(absConfigPath))
{
}

Parser	&Parser::operator = (const Parser &parser) {    //TODO dovrei controllare funzionino, pero non si usano (in caso commente)
    this->~Parser();
    ::new(this) Parser(parser);
    return (*this);
}

//Destructor
Parser::~Parser() {
    // std::cout << "Destructor called(Parser)" << std::endl;
}

//Setters

//Getters
const Server* Parser::getServer() {
    if (_serverVect.empty() || _tmpServer == 1) {
        _tmpServer = 0;
        return NULL;
    }
    const Server* tmpServer = &_serverVect[_currentServer];
    _currentServer = (_currentServer + 1) % _serverVect.size();  // Move to the next state, loop back if necessary
    if (_currentServer == 0)
        _tmpServer = 1;
    return tmpServer;
}

std::vector<Server> Parser::getServerVector() {
    return this->_serverVect;
}

std::string	Parser::getConfigFile() const
{
    return this->_configFile;
}

//Exceptions
const char* Parser::ConfigFileException::message = "The config file is invalid, as template see NGINX server block configuration.";
const char * Parser::ConfigFileException::what() const throw() {
    return this->message;
}
