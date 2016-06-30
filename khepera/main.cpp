#include <iostream>
#include <chrono>
#include <time.h>       /* time */

#include "room.h"
#include "posvec_struct.h"
//#include "khepera_agent.h"
#include "q_learning.h"
#include "random_action.h"   //When random actions are required
#include "save_files.h"
#include "load_files.h"
#include "khepera_test.h"

#include "bt_structure.h"
#include "bt_test.h"
#include "solution_method.h"

#include "bt_test_gp_kirk.h"
#include "../BT/btFile.h"
#include "../EvolutionaryLearning/GP.h"



using namespace BT_Structure;
using namespace BT;



int main(int argc, char *argv[])
{
    srand (time(NULL));

    bool SAVEDATA           = 1;
    bool RUN_SIMULATION     = 1;
    bool RUN_TPM            = 1;
    bool RUN_GP             = 0;
    Save save;
    //Load load;

    blackboard BB;
    Q_learning *sol_met = new Q_learning(0.5, 0.8, 0.05, 8, 3, &BB);
    Q_learning *sol_met1 = new Q_learning(&BB);
    bt_test_gp_kirk *sol_met2 = new BT::bt_test_gp_kirk(&BB);
    Random_action *sol_met3 = new Random_action();


    if(RUN_SIMULATION == 1)
    {
        // Calculate execution time
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        // Initiate World and Solution method objects
        Room room1(15,25);

        // Initiate Agent start at [3,4]
        Agent_H Khepera_heading(&room1, 3, 4, EAST, 8, 3, sol_met2, &BB, SAVEDATA);

        // Run Agent
        Khepera_heading.runAgent(2,150);

        if(SAVEDATA == 1)
        {
            save.printQtable(sol_met->Qtable);
        }


        // Calculate execution time
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        std::cout << "\n" << duration / 1000000 << " seconds" << "\n";
    }


    if(RUN_TPM == 1)
    {
        Khepera_T Khepera_test_agent(sol_met2, &BB);
        Khepera_test_agent.runKhepera_test(100, "1,1,1,3,1,1,1,1");
    }


    if(RUN_GP)
    {
        // Calculate execution time
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        Khepera_T Khepera_test_agent(&BB);
        Khepera_test_agent.runKhepera_wiht_GP(100, "1,1,1,3,1,1,1,1", &BB,50);

        // Calculate execution time
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        std::cout << "\n" << duration / 1000000 << " seconds" << "\n";
    }


    return 0;

}
