#include <iostream>

#include "room.h"
#include "posvec_struct.h"
#include "khepera_agent.h"
#include "q_learning.h"


int main(int argc, char *argv[])
{

    Room room1;
    Solution_method *sol_met = new Q_learning(0.5,0.5,10,3);

    Agent Khepera(&room1, 0,0, 10,sol_met);

    Khepera.current_action = UP;
    Khepera.performAction();
    Khepera.sol_met->SolutionMethodupdate(&Khepera);
    Khepera.current_action = DOWN;
    Khepera.performAction();
    Khepera.sol_met->SolutionMethodupdate(&Khepera);


    return 0;

}
