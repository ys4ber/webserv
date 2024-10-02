#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>

using namespace std;

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    fd_set readfds;
    int max_fd;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address and port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080); // Replace with desired port

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&readfds); // Clear readfds set
    FD_SET(server_socket, &readfds); // Add server socket to readfds
    max_fd = server_socket;

    while (true)
    {
        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity == -1)
        {
            perror("select failed");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(server_socket, &readfds))
        {
            client_address_length = sizeof(client_address);
            client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
            if (client_socket == -1)
            {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }

            FD_SET(client_socket, &readfds);
            max_fd = max(max_fd, client_socket);
        }

        for (int i = 0; i <= max_fd; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                char buffer[1024] = {0};
                ssize_t bytes_read = recv(client_socket, buffer, 1024, 0);
                if (bytes_read == -1)
                {
                    perror("recv failed");
                    exit(EXIT_FAILURE);
                }
                else if (bytes_read == 0)
                {
                    close(i);
                    FD_CLR(i, &readfds);
                }
                else
                {
                    cout << "Received: " << buffer << endl;
                }
            }
        }
    }

    return 0;
}