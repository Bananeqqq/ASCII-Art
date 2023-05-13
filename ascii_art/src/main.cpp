#include "Controller.hpp"
#include <iostream>


int main(int argc, char *argv[]) {

    try {
        Controller controller(argc, argv);
    }
    catch (std::exception &e){
        std::cout << "Main, error: " << e.what() << std::endl;
    }

    return 0;
}
