#include <iostream>
#include "taxiworld.h"
#include "agent.h"
#include "q_learning.h"
#include "position_struct.h"



int main()
{

    TaxiWorld Taxi_NY;

    Agent NY_Agent(&Taxi_NY,0,0);

    Solution_method* SOL_MET;
    SOL_MET = new Q_learning;

    NY_Agent.setSolutionMethod(SOL_MET);

    NY_Agent.runAgent();

    return 0;


}

