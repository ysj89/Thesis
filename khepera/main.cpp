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


        // /////////////
        // Define World and Agent objects
        // /////////////
        Room room1(20,40);
        Q_learning *sol_met = new Q_learning(0.5, 0.9, 0.5, 8, 3);

        // /////////////
        // Define Agent
        // /////////////
//      Agent Khepera(&room1, 5,5, 8, 4,sol_met,SAVEDATA);
        Agent_H Khepera_heading(&room1, 3, 7, EAST, 9, 3, sol_met, SAVEDATA);


        // /////////////
        // Run Agent
        // /////////////
//        Khepera.runAgent(500, 1000);
        Khepera_heading.runAgent(100000000,1000);



        std::stringstream filename;
        filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/QTable/QTable.txt";
        std::ofstream fs;
        fs.open(filename.str(), std::ios::out);
        Print::outputQTable(sol_met->Qtable, fs);
        fs.close();


    // Calculate execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\n" << duration / 1000000 << " seconds" << "\n"  ;

    return 0;

}
