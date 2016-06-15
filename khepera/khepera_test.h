#ifndef KHEPERA_TEST_H
#define KHEPERA_TEST_H

#include <chrono>
#include <random>

#include "load_files.h"
#include "transitionmatrix.h"
#include "solution_method.h"
#include "../EvolutionaryLearning/GP.h"

#include "bt_test_gp_kirk.h"




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
        transitionMatrix_discrete_distribution = load.loadTransitionMatrix_discrete_distribution();
        string2int = load.loadString2Int();

        // to get string from index
        for(auto kv : string2int)
        {
            keys.push_back(kv.first);
            vals.push_back(kv.second);
        }
    }
    Khepera_T(blackboard *BB)
        :   BLKB(BB),
          state_vec_temp(9)
    {
        Qtable = load.loadQtable1();
        transitionMatrix = load.loadTransitionMatrix();
        transitionMatrix_discrete_distribution = load.loadTransitionMatrix_discrete_distribution();
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


    double score_tree;

    std::unordered_map<std::string, ActionScoreMap> Qtable;
    std::vector<std::vector<std::vector<double> > >transitionMatrix;
    std::vector<std::vector<std::vector<int> > > transitionMatrix_discrete_distribution;
    std::unordered_map<std::string, int> string2int;

    std::vector<std::string> keys;
    std::vector<int> vals;
    std::vector<int> state_vec_temp;


    void runKhepera_test( int totalsteps, std::string start);
    void runKhepera_wiht_GP(int totalsteps, std::string start, blackboard *p_BLKB);
    void run_gen(GP::citizens* population, size_t k_run);
//    void save_path(std::string folder, citizen* best);

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();


    std::string transition(std::string state, int action);

    std::vector<int> getTransitions(std::string state, int action);
    //std::vector<int> getTransitions_count(std::string state, int action);
    std::string returnNextState(std::vector<int> transitionVector);
    std::string returnNextState_int(std::vector<int> transitionvec);
    std::vector<int> string2vec(std::string state);


};

#endif // KHEPERA_TEST_H
