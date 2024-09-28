#include "header.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Invalid args, run ./webserv config.conf" << std::endl;
        return -1;
    }
    std::fstream file(av[1]);
    if (!file.is_open())
    {
        std::cerr << "Invalid config file" << std::endl;
        return -1;
    }
    

}