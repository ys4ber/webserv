#include "header.hpp"
#include <cstdlib>

#define BUFFER_SIZE 1024

int main()
{
    int port = 8080;
    std::string path = "/old-page";
    std::string root = "/var/www/example";
    std::string server_name = "example.com";
    std::string host = "127.0.0.1";
    (void)port;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Binding the server FAILED" << std::endl;
        return -1;
    }

    if (listen(socket_fd, 10) == -1)
    {
        std::cerr << "Listening Failed" << std::endl;
        return -1;
    }

    std::cout << "Server are listening on port : " << port << std::endl;

    int client_socket = accept(socket_fd, NULL, NULL);

    char buffer[BUFFER_SIZE] = {0};

    recv(client_socket, buffer, sizeof(buffer), 0);

    std::cout << "Message from client : " << buffer << std::endl;

    close (socket_fd);
    close(client_socket);
}