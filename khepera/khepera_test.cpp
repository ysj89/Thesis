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
        int action = rand() % 3;


        // get new state

        state_new = transition(state, action);

        // get value new state

        ActionScoreMap as;
        as = Qtable[state_new];

        double score;
        score = as[action];
        score_total = score_total + score;

        state = state_new;
    }

    std::cout << "The total score is: " << score_total << std::endl;
}

std::string Khepera_T::transition(std::string state, int action)
{
    std::vector<double> probability;

    probability = getTransitions(state, action);

    double sum_of_elems = 0;

    for (double n : probability)
    {
        sum_of_elems += n;
    }

    if(sum_of_elems != 0)
    {

        std::string new_state = returnNextState(probability);
        std::cout << "The new state is: " <<new_state << std::endl;
        return new_state;
    }
    else
    {
        std::cout << "This transition did not happen during exploration/learning" << std::endl;
        return state;
    }
}

std::vector<double> Khepera_T::getTransitions(std::string state, int action)
{
    std::vector<double> TP;
    TP.reserve(string2int.size());
    int in_state = string2int[state];

    for(unsigned i = 0; i <  (transitionMatrix[1].size()); i++ )
    {
        TP.push_back(transitionMatrix[in_state][i][action]);
    }

    return TP;
}

std::string Khepera_T::returnNextState(std::vector<double> transitionVector)
{
    std::mt19937 gen(1701);
    std::discrete_distribution<> distr(transitionVector.begin(), transitionVector.end());
    unsigned next_state = distr(gen);

    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), next_state);
    int pos = std::distance(vals.begin(), it);

    std::string new_state = keys[pos];

    return new_state;
}


