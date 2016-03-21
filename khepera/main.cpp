#include <iostream>

#include "room.h"
#include "posvec_struct.h"
#include "khepera_agent.h"
#include "q_learning.h"


int main(int argc, char *argv[])
{

    Room room1(8,10);
    Solution_method *sol_met = new Q_learning(0.5,0.5,0.5,10,3);

    Agent Khepera(&room1, 1,1, 8,sol_met);


    room1.setWall();
//    room1.initializeTrash();
    room1.printWorldMap();

    Khepera.runAgent(10, 500);
    Khepera.printAgentinRoom();
//    room1.printWorldMap();

    return 0;

}
