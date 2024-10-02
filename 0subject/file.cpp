#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

const int BUFFER_SIZE = 1024;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8082);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind to port" << std::endl;
        return 1;
    }

    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080" << std::endl;

    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }

        // Read the HTTP request
        char buffer[BUFFER_SIZE] = {0};
        ssize_t bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytesRead < 0) {
            std::cerr << "Failed to read from socket" << std::endl;
            close(clientSocket);
            continue;
        }

        // Parse the request (very basic parsing)
        std::string request(buffer);
        std::istringstream iss(request);
        std::string requestLine;
        std::getline(iss, requestLine);
        
        std::cout << "Received request: " << requestLine << std::endl;

        // Prepare and send a response
        std::string htmlContent = "<html><body><h1>Hello from C++98 Webserver!</h1></body></html>";
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: ";
        
        // C++98 compatible way to convert int to string
        std::ostringstream contentLengthStream;
        contentLengthStream << htmlContent.length();
        response += contentLengthStream.str();
        
        response += "\r\n\r\n";
        response += htmlContent;

        send(clientSocket, response.c_str(), response.length(), 0);

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}