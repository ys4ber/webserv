#include "header.hpp"

int main()
{
    // if (ac != 2)
    // {
    //     std::cerr << "Invalud number of arguments" << std::endl;
    //     std::cerr << "run ./webserv config.conf" << std::endl;
    //     return -1;
    // }

    // std::fstream file(av[1]);
    // if (!file.is_open())
    // {
    //     std::cerr << "Invalid config file " << std::endl;
    //     return -1;
    // }
    int i  = 0;
    int port = 3412;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Creating socket: FAILED" << std::endl;
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    int a = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(a < 0)
    {
        std::cerr << "Binding the port: FAILED" << std::endl;
        return -1;
    }

    if (listen(serverSocket, 10) < 0)
    {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }
    std::cout << "server are listening on port : " << port << std::endl;

    while (true)
    {
        sockaddr_in c_addr;
        socklen_t c_addr_len = sizeof (c_addr);
        int c_socket = accept(serverSocket, (struct sockaddr *)&c_addr, &c_addr_len);
        
        if (c_socket < 0)
        {
            std::cerr << "efsfsfs" << std::endl;
            continue;
        }
        i++;
        char buffer[1024] = {0};

        ssize_t b_read = recv(c_socket, buffer, 1024 -1, 0);

        if (b_read == -1)
        {
            std::cerr << "Failed to read from socket  1" << std::endl;
            close(c_socket);
            continue;
        }

        std::cout << "B_read : " << b_read << std::endl;

        std::string req = buffer;
        std::istringstream iss(req);
        std::string req_line;
        std::getline(iss, req_line);

        std::cout << "Recieved req : " << req_line << std::endl;

        std::string htmlcont = "Hahahahahahhahahaha";
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: ";

        std::ostringstream cont_leng;

        cont_leng << htmlcont.length();

        response += cont_leng.str();

        response += "\r\n\r\n";
        response += htmlcont;
        std::cout << "this is i :  " << i << std::endl;
        
        send(c_socket, response.c_str(), response.length(), 0);

        close(c_socket);
    }

    close(serverSocket);
    return 0;
    
}