#include <iostream>

using namespace std;

//Fuction to check if protocol is valid
bool checkProtocol(string protocol)
{
    //Checks if protocol is one of the valid protocols. If it is returns true
    if((protocol == "https") || (protocol == "http") || (protocol == "ftps") || (protocol == "ftp"))
    {
        return true;
    }
    //If protocol is not valid return false
    else
    {
        return false;
    }
}

//Fuction to check if domain is valid
bool checkDomain(string domain)
{
    //Extract the end of the domain
    domain = domain.substr(domain.length() - 3);
    
    //Checks if domain is one of the valid domains. If it is returns true
    if((domain == "com") || (domain == "net") || (domain == "edu") || (domain == "biz") || (domain == "gov"))
    {
        return true;
    }
    //If domain is not valid return false
    else
    {
        return false;
    }
}

//Fuction to check if there is a port
bool checkPort(string url)
{
    //If there is not port return false
    if(url.find(":") == -1)
    {
        return false;
    }
    //If there is a port return true
    else
    {
        return true;
    }
}

//Fuction to check if there are parameters
bool checkParameters(string url)
{
    //If there are no parameters return false
    if(url.find("?") == -1)
    {
        return false;
    }
    //If there are parameters return true
    else
    {
        return true;
    }
}

//Fuction to check if file path is valid
bool checkFilePath(string filePath)
{
    //Checks if file path is valid. If it is returns true
    if((filePath.substr(filePath.find(".")) == ".html") || (filePath.substr(filePath.find(".")) == ".htm"))
    {
        return true;
    }
    //If file path is not valid return false
    else
    {
        return false;
    }
}

//Function to check is port number is valid
int checkPortNum(string port)
{
    //Check if there is a port number (i.e. string port is not an empty string)
    if(port == "0")
    {
        return 0;
    }
    //If there is a port check if it is in the range
    else
    {
        int portNum = stoi(port);
        
        if((portNum >= 1) && (portNum <= 65535))
        {
            return portNum;
        }
        else
        {
            return -1;
        }
    }
}

//Print the information
void print(string protocol, string domain, string port, string filePath, string parameters)
{
    //Check if domain, protocol and file path is valid
    if(checkProtocol(protocol) && checkDomain(domain) && checkFilePath(filePath))
    {
        //Check if the port is present
        if(checkPortNum(port) == 0)
        {
            //If no port print all other informations
            cout << "Protocol:    " << protocol << "\nDomain:      " << domain << "\nFile Path:   " << filePath;
            //If there are parameters print them
            if(parameters != "")
            {
                cout << "\nParameters:  " << parameters;
            }
        }
        //If there is a port but it is not valid print an error message
        else if(checkPortNum(port) == -1)
        {
            cout << "Invalid URL with following erroneous components:\nPort:\tport number must be between 1 and 65535";
        }
        //If port is valid print all information
        else
        {
            cout << "Protocol:    " << protocol << "\nDomain:      " << domain << "\nFile Path:   " << filePath << "\nPort:        " << port;
            //If there are parameters print them
            if(parameters != "")
            {
                cout << "\nParameters:  " << parameters;
            }
        }
    }
    //If domain, protocol or file path is not valid
    else
    {
        //Print error message
        cout << "\nInvalid URL with following erroneous components:\n";
        
        //For each componenet check if it is valid and if not print the error
        if(!checkProtocol(protocol))
        {
            cout << "Protocol:    " << protocol << " is not a valid protocol.\n";
        }
        if(!checkDomain(domain))
        {
            cout << "Domain:      " << domain << " is not a valid domain.\n";
        }
        if(!checkFilePath(filePath))
        {
            cout << "File Path:  " << " file path must end with .html or .htm\n";
        }
        if(checkPortNum(port) == -1)
        {
            cout << "Port:        port number must be between 1 and 65535\n";
        }
    }
}

//main functionn
int main()
{
    //Strings to store URL and components
    string url;
    string protocol, domain, port, filePath, parameters;
    
    //Take in URL from user
    cout << "Enter URL: ";
    getline(cin, url);
    
    //Extract elements from URL by checking for the ones present
    protocol = url.substr(0, url.find(":"));
    url = url.substr(url.find("//") + 2);
    
    if(checkPort(url))
    {
        domain = url.substr(0, url.find(":"));
        url = url.substr(url.find(":") + 1);
        port = url.substr(0, url.find("/"));
        url = url.substr(url.find("/"));
    }
    else
    {
        domain = url.substr(0, url.find("/"));
        url = url.substr(url.find("/"));
    }
    
    if(checkParameters(url))
    {
        filePath = url.substr(0, url.find("?"));
        parameters = url.substr(url.find("?") + 1, url.find("#"));
    }
    else
    {
        filePath = url;
    }
    
    //Print gathered information with print function
    print(protocol, domain, port, filePath, parameters);
    
    return 0;
}
