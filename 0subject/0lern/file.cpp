#include <iostream>
#include <cstring>  // For memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>  // For close()

int main()
{
    int serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8082);

    int bb;
     
    bb = bind(serversocket, (struct sockaddr *)&addr, sizeof(addr));

    if (bb < 0) 
    {
        std::cerr << "Waaaaaaaaa3 1" <<std::endl;
        return -1;
    }

    listen()
    
}