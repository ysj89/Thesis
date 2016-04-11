#include <iostream>
#include <chrono>

#include "room.h"
#include "posvec_struct.h"
#include "khepera_agent.h"
#include "q_learning.h"
#include "random_action.h"
#include "save_files.h"


int main(int argc, char *argv[])
{
    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        bool SAVEDATA = 1;
        Save save;

        // /////////////
        // Define World and Agent objects
        // /////////////
        Room room1(15,25);
        Q_learning *sol_met = new Q_learning(0.5, 0.8, 0.3, 8, 3);
//        Random_action *sol_met1 = new Random_action();

        // /////////////
        // Define Agent
        // /////////////
//        Agent Khepera(&room1, 5,5, 8, 4,sol_met,SAVEDATA);
        Agent_H Khepera_heading(&room1, 3, 4, EAST, 9, 3, sol_met, SAVEDATA);

        // /////////////
        // Run Agent
        // /////////////
//         Khepera.runAgent(1000, 500);
        Khepera_heading.runAgent(100000,500);

        if(SAVEDATA == 1)
        {
            save.printQtable(sol_met->Qtable);
        }

    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\n" << duration / 1000000 << " seconds" << "\n";

    return 0;

}
