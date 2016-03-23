#include <iostream>
#include <chrono>

#include "room.h"
#include "posvec_struct.h"
#include "khepera_agent.h"
#include "q_learning.h"


int main(int argc, char *argv[])
{
        // Calculate execution time
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        bool SAVEDATA = 1;

        // Define World and Agent objects
        Room room1(20,30);
        Solution_method *sol_met = new Q_learning(0.5,0.5,0.5,10,3);
        Agent Khepera(&room1, 5,5, 8,sol_met,SAVEDATA);

        // Set mission
//        room1.setWall();

        // Run Agent
        Khepera.runAgent(500, 1000);
//        room1.printWorldMap();

    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\n" << duration / 1000000 << "seconds" << "\n"  ;

    return 0;

}
