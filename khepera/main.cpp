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

        bool SAVEDATA = 1;
        bool RUN = 1;
        bool LOAD = 0;
        Save save;
        Load load;


        if(RUN == 0)
        {
        // /////////////
        // Initiate World and Solution method objects
        // /////////////
        Room room1(15,25);
        blackboard *BLKB;

        Q_learning *sol_met = new Q_learning(0.5, 0.8, 0.01, 8, 3, BLKB);
        //BehaviorTree *sol_met_bt = new BehaviorTree;
        //Random_action *sol_met1 = new Random_action();

        // /////////////
        // Initiate Agent
        // /////////////
        Agent_H Khepera_heading(&room1, 3, 4, EAST, 9, 3, sol_met, SAVEDATA);


        // /////////////
        // Run Agent
        // /////////////
        Khepera_heading.runAgent(4500,150);

        if(SAVEDATA == 1)
        {
            save.printQtable(sol_met->Qtable);
        }
        }


        std::unordered_map<std::string, ActionScoreMap> Qtable;
        std::vector<std::vector<std::vector<double> > >transitionPM;
        std::unordered_map<std::string, int> string2intConversion;

        if(LOAD == 1)
        {
        Qtable = load.loadQtable1();
        transitionPM = load.loadTransitionMatrix();
        string2intConversion = load.loadString2Int();
        }


        // BT TEST CODE
        Room room1(15,25);
        BehaviorTree *sol_met_bt = new BehaviorTree;
        Agent_H Khepera_heading_bt(&room1, 3, 4, EAST, 9, 3, sol_met_bt, SAVEDATA);

        Khepera_heading_bt.runAgent(100,10);



    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\n" << duration / 1000000 << " seconds" << "\n";

    return 0;

}
