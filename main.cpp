#include <iostream>
#include <signal.h>
#include "include/mainloop.hpp"

void sigIntHandler(int s)
{
    std::cout << "SigIntHandler " << s << std::endl;
    exit(1);
}

int main(/*int argc, char* argv[]*/)
{
    try {
        signal(SIGINT, sigIntHandler);
        mainLoop().execute();
    } catch (const std::exception& e) {
        std::cerr << "[Mario] " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "[Mario] Unknown exception" << std::endl;
    }
    return 1;
}
