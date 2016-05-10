#include <algorithm>    // std::find
#include <random>       // random

#include "khepera_test.h"
#include "load_files.h"
#include "transitionmatrix.h"


void Khepera_T::runKhepera_test(int totalsteps, std::string start)
{

    TransitionMatrix TM1(500, 3);

    double score_total;
    std::string state = start;
    std::string state_new;

    for(int steps = 0; steps < totalsteps; steps++)
    {
        // Get action from choose-method
        int action; //  = rand() % 3;

        sol_met->chooseAction(BLKB);
        action = static_cast<int> (BLKB->get("action") ); // read action from blackboard

        // get new state
        state_new = transition(state, action);

        // get value new state
        ActionScoreMap as;
        as = Qtable[state_new];

        double score;
        score = as[action];
        score_total = score_total + score;

        // convert state back to vector and put on BB
        state_vec_temp = string2vec(state_new);
        BLKB->set("sensor0", state_vec_temp[0]);
        BLKB->set("sensor1", state_vec_temp[1]);
        BLKB->set("sensor2", state_vec_temp[2]);
        BLKB->set("sensor3", state_vec_temp[3]);
        BLKB->set("sensor4", state_vec_temp[4]);
        BLKB->set("sensor5", state_vec_temp[5]);
        BLKB->set("sensor6", state_vec_temp[6]);
        BLKB->set("sensor7", state_vec_temp[7]);

        state = state_new;
    }

    std::cout << "The total score is: " << score_total << std::endl;
}

std::vector<int> Khepera_T::string2vec(std::string state)
{
        std::vector<int> state_vec;

        // Fill DataNumbers
        for (int i=0; i < 17; i+=2 )
        {
            char s = state.at(i);
            int int_state = s - 48 ;
            state_vec.push_back(int_state);
        }
        return state_vec;
}

std::string Khepera_T::transition(std::string state, int action)
{
    std::vector<int> discrete_distribution_vec;

    discrete_distribution_vec = getTransitions(state, action);

    double sum_of_elems = 0;

    for (int n : discrete_distribution_vec)
    {
        sum_of_elems += n;
    }

    if(sum_of_elems != 0)
    {

        std::string new_state = returnNextState(discrete_distribution_vec);
        std::cout << "The new state is: " <<new_state << std::endl;
        return new_state;
    }
    else
    {
        std::cout << "This transition did not happen during exploration/learning" << std::endl;
        return state;
    }
}

std::vector<int> Khepera_T::getTransitions(std::string state, int action)
{
    std::vector<int> TP;
    TP.reserve(string2int.size());
    int in_state = string2int[state];

    for(unsigned i = 0; i <  (transitionMatrix_discrete_distribution[1].size()); i++ )
    {
        TP.push_back(transitionMatrix_discrete_distribution[in_state][i][action]);
    }

    return TP;
}

std::string Khepera_T::returnNextState(std::vector<int> transitionVector)
{
    //std::mt19937 gen(1701);
    std::default_random_engine generator(seed1);

    std::discrete_distribution<> distr(transitionVector.begin(), transitionVector.end());

    unsigned next_state = distr(generator);

    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), next_state);
    int pos = std::distance(vals.begin(), it);

    std::string new_state = keys[pos];

    return new_state;
}


