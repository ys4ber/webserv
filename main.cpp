#include "header.hpp"


void ft_fill_data(t_serv *serv, std::string file)
{
    std::ifstream ifs(file.c_str());
    std::string line;
    std::string key;
    std::string value;
    while (std::getline(ifs, line))
    {
        if(line.empty())
            continue;
        if(line.find("server") != std::string::npos)
        {
            
        }
    } 
}


int main(int ac , char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        return 1;
    }
    if (access(av[1], F_OK) == -1)
    {
        std::cerr << "File " << av[1] << " does not exist" << std::endl;
        return 1;
    }
    std::string file = av[1];
    t_serv *serv = new t_serv;
    ft_fill_data(serv, file);

    
}