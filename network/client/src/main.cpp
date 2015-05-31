#include <sstream>
#include "stdlib.h"
#include "NetworkManager.hpp"


int getPortNumber() {
    std::string     input;
    bool            found = false;
    int             default_port = 4242;
    int             ret;
    std::string     input_string;

    while (found == false) {
        std::cout << "Enter a port number (4242) :" << std::endl;

        std::getline(std::cin, input);
        if (!input.empty()) {
            std::istringstream stream(input);
            stream >> input_string;
            ret = atoi(input_string.c_str());
            if (ret != 0) {
                found = true;
            }
        } else {
            found = true;
            ret = 4242;
        }
    }
    return (ret);
}

int main(int argc, char *argv[]) {
    NetworkManager *nm = new NetworkManager(getPortNumber());
    nm->run();
    return 0;
}

// get inputs
// get network non-bloquant
// manage inputs/network
// send network
// display