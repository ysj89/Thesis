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
    TransitionMatrix(unsigned size_tm, unsigned num_of_actions);

    // Main interface
    int get(std::string x1, std::string x2);
    void increment(StateVec state_1, StateVec state_2, int action);
    void sumTransitions(unsigned size_tm, int num_of_action);
    void calculateTPM(unsigned size_tm, int num_of_action);
    void getTP(std::string state1, std::string state2);

    // string2intMap interface
    unsigned getIndexFromString1(std::string s);

    std::vector<std::vector<double> > TPM;
    std::vector<std::vector<std::vector<double> > > TPM2;
    std::unordered_map<std::string, unsigned> string2intMap1;



private:

//    std::vector<std::vector<unsigned> > transitionMatrix;
    std::vector<std::vector<std::vector<unsigned> > > transitionMatrix;
    unsigned currentStringIndex1;


    std::vector<std::vector<int> > sum_of_row_vec;
};

#endif // TRANSITIONMATRIX_H
