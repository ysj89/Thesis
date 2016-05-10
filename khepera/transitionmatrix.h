#ifndef TRANSITIONMATRIX_H
#define TRANSITIONMATRIX_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "posvec_struct.h"


class TransitionMatrix
{
public:
    TransitionMatrix(unsigned size_tm, unsigned num_of_actions)
        : currentStringIndex1(0)
{   // Unsigned vs Int
    transitionMatrix_count = std::vector<std::vector<std::vector<unsigned> > > {size_tm,std::vector<std::vector<unsigned> > (size_tm, std::vector<unsigned>(num_of_actions,0))};
    sum_of_row_vec = std::vector<std::vector<int> >{size_tm, std::vector<int>(num_of_actions,0)};
    TPM = std::vector<std::vector<std::vector<double> > >{size_tm, std::vector<std::vector<double> >(size_tm,std::vector<double>(num_of_actions,0))};

    keys.reserve(size_tm);
    vals.reserve(size_tm);
}


    // Main interface
    int get(std::string x1, std::string x2);
    void increment(StateVec state_1, StateVec state_2, int action);
    void sumTransitions(unsigned size_tm, int num_of_action);
    void calculateTPM(unsigned size_tm, int num_of_action);
    void getTP(std::string state1, std::string state2);


    std::vector<double> getTransitionsForState(std::string state1, int action);
    std::vector<int> getTransitionsForState_number(std::string state1, int action);
    std::string returnNextState_double(std::vector<double> TPvec);
    std::string returnNextState_int(std::vector<int> TPvec);
    //std::pair<std::string, double> transition_full(std::string state1, int action, std::unordered_map<std::string, ActionScoreMap> m_Qtable);
    std::string transition(std::string state1, int action);

    void storeKeyandMap();

    // string2intMap interface
    unsigned getIndexFromString1(std::string s);
    std::string getStringFromIndex(unsigned index);
    void TransitionMatrixCOUT(std::string s);


    std::vector<std::vector<std::vector<double> > > TPM;
    std::unordered_map<std::string, unsigned> string2intMap1;
    std::vector<std::vector<std::vector<unsigned> > > transitionMatrix_count;



private:
    std::vector<std::string> keys;
    std::vector<int> vals;

    //    std::vector<std::vector<unsigned> > transitionMatrix;
    unsigned currentStringIndex1;



    std::vector<std::vector<int> > sum_of_row_vec;
};

#endif // TRANSITIONMATRIX_H
