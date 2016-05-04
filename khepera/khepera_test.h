#ifndef KHEPERA_TEST_H
#define KHEPERA_TEST_H

#include "load_files.h"
#include "transitionmatrix.h"
#include "solution_method.h"

class Khepera_T
{
public:
    Khepera_T(Solution_method *_sol_met, blackboard *BB)
        : sol_met(_sol_met),
          BLKB(BB),
          state_vec_temp(9)
    {
        Qtable = load.loadQtable1();
        transitionMatrix = load.loadTransitionMatrix();
        string2int = load.loadString2Int();

        // to get string from index
        for(auto kv : string2int)
        {
            keys.push_back(kv.first);
            vals.push_back(kv.second);
        }
    }

    Solution_method *sol_met;
    blackboard *BLKB;
    Load load;

    std::unordered_map<std::string, ActionScoreMap> Qtable;
    std::vector<std::vector<std::vector<double> > >transitionMatrix;
    std::unordered_map<std::string, int> string2int;

    std::vector<std::string> keys;
    std::vector<int> vals;
    std::vector<int> state_vec_temp;

    void runKhepera_test(int totalsteps, std::string start);

    std::string transition(std::string state, int action);

    std::vector<double> getTransitions(std::string state, int action);
    std::string returnNextState(std::vector<double> transitionVector);
    std::vector<int> string2vec(std::string state);


};

#endif // KHEPERA_TEST_H
