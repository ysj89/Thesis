//#include "iostream"
#include <algorithm>    // std::find
#include "transitionmatrix.h"
#include "save_files.h"


TransitionMatrix::TransitionMatrix(unsigned size_tm, unsigned num_of_actions) :
    currentStringIndex1(0)
{   // Unsigned vs Int
    transitionMatrix = std::vector<std::vector<std::vector<unsigned> > > {size_tm,std::vector<std::vector<unsigned> > (size_tm, std::vector<unsigned>(num_of_actions,0))};
    sum_of_row_vec = std::vector<std::vector<int> >{size_tm, std::vector<int>(num_of_actions,0)};
    TPM = std::vector<std::vector<double> > {size_tm, std::vector<double>(size_tm,0)};
    TPM2 = std::vector<std::vector<std::vector<double> > >{size_tm, std::vector<std::vector<double> >(size_tm,std::vector<double>(num_of_actions,0))};

    keys.reserve(size_tm);
    vals.reserve(size_tm);
}


void TransitionMatrix::increment(StateVec state_1, StateVec state_2, int action)
{
    std::string x1 = vec2str(state_1);
    std::string x2 = vec2str(state_2);

    unsigned i1 = getIndexFromString1(x1);
    unsigned i2 = getIndexFromString1(x2);

    transitionMatrix[i1][i2][action] = ++transitionMatrix[i1][i2][action];
}

void TransitionMatrix::sumTransitions(unsigned size_tm, int num_of_action)
{
    for(int a; a < num_of_action; a++)
    {
        for(unsigned int i = 0; i < size_tm; i++ )
        {
            for(unsigned int j = 0; j < size_tm; j++ )
            {
                sum_of_row_vec[i][a] = sum_of_row_vec[i][a] + transitionMatrix[i][j][a];
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
                    TPM2[i][j][a] = 0;
                }
                else
                {
                    TPM2[i][j][a] = transitionMatrix[i][j][a] / (double) sum_of_row_vec[i][a];
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
        std::cout<< "Transition probabilityes from " << state1 << " to " << state2 << " are: " << TPM2[x1][x2][0] << " " << TPM2[x1][x2][1] << " " << TPM2[x1][x2][2] << std::endl;
    }
    else
    {
        std::cout << "TRANSITION MATRIX: States not transitioned during run" << std::endl;
    }
}

std::vector<double> TransitionMatrix::getTP2(StateVec state1, int action)
{
    std::vector<double> TP;

    std::string str_state = vec2str(state1);
    int in_state = string2intMap1[str_state];

    for(unsigned i = 0; i <  (TPM2[1].size() + 1); i++ )
    {
        TP[i] = TPM2[in_state][i][action];
    }

    return TP;
}

std::string TransitionMatrix::returnNextState(std::vector<double> TPvec)
{
    // Using the transition vector, return index
    // transform index to state

    unsigned next_state;


    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), next_state);
    std::string new_state = keys[*it];

    return new_state;

}

void TransitionMatrix::storeKeyandMap(std::unordered_map<std::string, unsigned> stateID)
{

    for(auto kv : stateID) {
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




//void TransitionMatrix::calculatePTM(unsigned size_tm)
//{

//    sumTransitions(size_tm);

//    for(unsigned int i = 0; i < size_tm; i++ )
//    {
//        for(unsigned int j = 0; j< size_tm; j++ )
//        {
//            if(sum_of_row_vec[i] == 0)
//            {
//                TPM[i][j] = 0;
//            }
//            else
//            {
//                TPM[i][j] = transitionMatrix[i][j] / (double) sum_of_row_vec[i];
//            }
//        }
//    }
//}

