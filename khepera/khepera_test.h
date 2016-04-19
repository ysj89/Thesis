#ifndef KHEPERA_TEST_H
#define KHEPERA_TEST_H

#include "load_files.h"
#include "transitionmatrix.h"

class Khepera_T
{
public:
    Khepera_T()
{


        Qtable = load.loadQtable1();
        transitionMatrix = load.loadTransitionMatrix();
        string2int = load.loadString2Int();

        for(auto kv : string2int) { // to get string from index
            keys.push_back(kv.first);
            vals.push_back(kv.second);
        }
}

    Load load;

    std::unordered_map<std::string, ActionScoreMap> Qtable;
    std::vector<std::vector<std::vector<double> > >transitionMatrix;
    std::unordered_map<std::string, int> string2int;

    std::vector<std::string> keys;
    std::vector<int> vals;

    void runKhepera_test(int totalsteps, std::string start);

    std::string transition(std::string state, int action);

    std::vector<double> getTransitions(std::string state, int action);
    std::string returnNextState(std::vector<double> transitionVector);






};

#endif // KHEPERA_TEST_H
