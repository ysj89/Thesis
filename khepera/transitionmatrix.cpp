//#include "iostream"
#include <algorithm>    // std::find
#include <random>       // random


#include "transitionmatrix.h"
#include "save_files.h"



void TransitionMatrix::increment(StateVec state_1, StateVec state_2, int action)
{

    std::string x1 = vec2str(state_1);
    std::string x2 = vec2str(state_2);
    unsigned i1 = getIndexFromString1(x1);
    unsigned i2 = getIndexFromString1(x2);

    transitionMatrix_count[i1][i2][action] = ++transitionMatrix_count[i1][i2][action];
}

void TransitionMatrix::sumTransitions(unsigned size_tm, int num_of_action)
{
    for(int a; a < num_of_action; a++)
    {
        for(unsigned int i = 0; i < size_tm; i++ )
        {
            for(unsigned int j = 0; j < size_tm; j++ )
            {
                sum_of_row_vec[i][a] = sum_of_row_vec[i][a] + transitionMatrix_count[i][j][a];
            }
        }
    }
}

void TransitionMatrix::calculateTPM(unsigned size_tm, int num_of_action)
{
    sumTransitions(size_tm, num_of_action);

    for(int a = 0; a < num_of_action; a++)
    {
        for(unsigned int i = 0; i < size_tm; i++ )
        {
            for(unsigned int j = 0; j< size_tm; j++ )
            {
                if(sum_of_row_vec[i][a] == 0)
                {
                    TPM[i][j][a] = 0;
                }
                else
                {
                    TPM[i][j][a] = transitionMatrix_count[i][j][a] / (double) sum_of_row_vec[i][a];
                }
            }
        }
    }
}

void TransitionMatrix::getTP(std::string state1, std::string state2)
{

    if(string2intMap1.find(state1) != string2intMap1.end() || string2intMap1.find(state2) != string2intMap1.end())
    {
        unsigned int x1 = string2intMap1[state1];
        unsigned int x2 = string2intMap1[state2];
        std::cout << "state1: " << x1 << " " << "state2: " <<  x2 << std::endl;
        std::cout<< "Transition probabilityes from " << state1 << " to " << state2 << " are: " << TPM[x1][x2][0] << " " << TPM[x1][x2][1] << " " << TPM[x1][x2][2] << std::endl;
    }
    else
    {
        std::cout << "TRANSITION MATRIX: States not transitioned during run" << std::endl;
    }
}

std::vector<double> TransitionMatrix::getTransitionsForState(std::string state1, int action)
{
    std::vector<double> TP;
    TP.reserve(string2intMap1.size());
    int in_state = string2intMap1[state1];

    for(unsigned i = 0; i <  (TPM[1].size()); i++ )
    {
        TP.push_back(TPM[in_state][i][action]);
    }

    return TP;
}

std::string TransitionMatrix::returnNextState(std::vector<double> TPvec)
{

    std::mt19937 gen(1701);
    std::discrete_distribution<> distr(TPvec.begin(), TPvec.end());
    unsigned next_state = distr(gen);

    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), next_state);
    int pos = std::distance(vals.begin(), it);

    std::string new_state = keys[pos];


    return new_state;

}

std::string TransitionMatrix::transition(std::string state1, int action)
{
    std::vector<double> probability;

    probability = getTransitionsForState(state1, action);

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
        return state1;
    }

}

//std::pair<std::string, double> TransitionMatrix::transition_full(std::string state1, int action, std::unordered_map<std::string, ActionScoreMap> m_Qtable)
//{
//    std::pair<std::string, double> stateScorePair;
//    std::vector<double> probability;

//    probability = getTransitionsForState(state1, action);

//    double sum_of_elems = 0;

//    for (double n : probability)
//    {
//        sum_of_elems += n;
//    }

//    if(sum_of_elems != 0)
//    {
//        ActionScoreMap Qscore;
//        double score;
//        std::string new_state = returnNextState(probability);


//        Qscore = m_Qtable[new_state];

//        score = Qscore[action];

//        stateScorePair.first = new_state;
//        stateScorePair.second = score;

//        std::cout << "The new state is: " <<new_state << "\t With a score of: " << score << std::endl;
//        return stateScorePair;
//    }
//    else
//    {
//        std::cout << "This transition did not happen during exploration/learning" << std::endl;
//        stateScorePair.first = state1;
//        stateScorePair.second = 0.0;

//        return stateScorePair;
//        return stateScorePair;
//    }



//}

void TransitionMatrix::storeKeyandMap()
{
    for(auto kv : string2intMap1)
    {
        keys.push_back(kv.first);
        vals.push_back(kv.second);
    }
}


unsigned TransitionMatrix::getIndexFromString1(std::string s)
{

    if(string2intMap1.find(s) == string2intMap1.end())
    {
        string2intMap1[s] = currentStringIndex1++;
    }

    return string2intMap1[s];
}

std::string TransitionMatrix::getStringFromIndex(unsigned index)
{
    for(auto kv : string2intMap1) {
        keys.push_back(kv.first);
        vals.push_back(kv.second);
    }

    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), index);
    int pos = std::distance(vals.begin(), it);
    std::string new_state = keys[pos];

    return new_state;
}



void TransitionMatrix::TransitionMatrixCOUT(std::string s)
{

    std::cout <<  string2intMap1[s] << std::endl;
}





