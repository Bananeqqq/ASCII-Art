#include "Controller.hpp"
#include <iostream>

int main(int argc, char *argv[])
{

    try
    {
        Controller controller(argc, argv);
    }
    catch (std::exception &e)
    {
        if (e.what() == std::string("stoi") || e.what() == std::string("stod"))
        {
            std::cout << "Error while parsing operation arguments" << std::endl;
        }
        else
        {
            std::cout << e.what() << std::endl;
        }
        return 1;
    }

    return 0;
}
