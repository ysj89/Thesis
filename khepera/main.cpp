#include <iostream>

#include "room.h"
#include "posvec_struct.h"
#include "khepera_agent.h"


int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;

    Room room1;

    Agent Khepera(&room1, 0,0);

    room1.printWorldMap();


    return 0;

}
