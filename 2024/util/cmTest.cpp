#include "chronoMessage.h"
#include <iostream>
#include <unistd.h>

ChronoMessage cm;

int main(int argc, char** argv){
    std::string message ("Hello Message");
    std::cout << cm.beginLog() << std::endl;
    usleep(600000);
    std::cout << cm.beginLog() << std::endl;
    usleep(400000);
    std::cout << cm.beginLog() << std::endl;
    usleep(400000);
    std::cout << cm.beginLog() << " " << 2 << " -"<< "Hello" << std::endl;
    std::cout << cm.beginLog() << "last line" << std::endl;
 
    return 0;
}
