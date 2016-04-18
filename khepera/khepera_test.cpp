
#include "khepera_test.h"
#include "load_files.h"
#include "transitionmatrix.h"


void Khepera_T::runKhepera_test(int totalsteps, std::string start)
{
    std::unordered_map<std::string, ActionScoreMap> Qtable;
    Qtable = load.loadQtable1();
    TransitionMatrix TM1(500, 3);
    double totalscore;

    for(int steps = 0; steps < totalsteps; steps++)
    {
        int action = rand() % 3;
        std::string new_state;
        new_state = TM1.transition(start, action);
        ActionScoreMap as;

        as = Qtable[new_state];
        double score;

        score = as[action];

        totalscore = totalscore + score;
    }
}
