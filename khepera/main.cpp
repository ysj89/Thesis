#include <iostream>
#include <chrono>

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



using namespace BT_Structure;

int main(int argc, char *argv[])
{
    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    bool SAVEDATA = 0;
    bool RUN = 0;
    bool TESTCASE = 1;
    Save save;
    //Load load;


    if(RUN == 1)
    {
        // /////////////
        // Initiate World and Solution method objects
        // /////////////
        Room room1(15,25);
        blackboard BB;
        Q_learning *sol_met = new Q_learning(0.5, 0.8, 0.01, 8, 3, &BB);
        //BehaviorTree *sol_met = new BehaviorTree(&BB);
        //Random_action *sol_met = new Random_action();

        // /////////////
        // Initiate Agent
        // /////////////
        Agent_H Khepera_heading(&room1, 3, 4, EAST, 9, 3, sol_met, &BB, SAVEDATA);

        // /////////////
        // Run Agent
        // /////////////
        Khepera_heading.runAgent(1,150);

        if(SAVEDATA == 1)
        {
            save.printQtable(sol_met->Qtable);
        }

    }


    //        std::unordered_map<std::string, ActionScoreMap> Qtable;
    //        std::vector<std::vector<std::vector<double> > >transitionPM;
    //        std::unordered_map<std::string, int> string2intConversion;

    //        if(LOAD == 1)
    //        {
    //        Qtable = load.loadQtable1();
    //        transitionPM = load.loadTransitionMatrix();
    //        string2intConversion = load.loadString2Int();
    //        }

    if(TESTCASE == 1)
    {
        // BT TEST CODE
        SAVEDATA = 0;
        Room room1(15,25);
        blackboard BB;
        BehaviorTree *sol_met = new BehaviorTree(&BB);
        //Random_action *sol_met = new Random_action();
        //Agent_H Khepera_heading_bt(&room1, 3, 4, EAST, 9, 3, sol_met, &BB, SAVEDATA);

        Khepera_T Khepera_test_agent(sol_met, &BB);
        Khepera_test_agent.runKhepera_test(150, "1,1,1,3,1,1,1,1,0");
    }

    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\n" << duration / 1000000 << " seconds" << "\n";

    return 0;

}
