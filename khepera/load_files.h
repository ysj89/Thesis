#ifndef LOAD_FILES_H
#define LOAD_FILES_H

#include "posvec_struct.h"
struct Load
{
    static std::unordered_map<std::string, ActionScoreMap> loadQtable1();
    std::vector<std::vector<std::vector<double> > > loadTransitionMatrix();
    std::vector<std::vector<std::vector<int> > > loadTransitionMatrix_discrete_distribution();
    std::unordered_map<std::string, int> Qconversion();
};

#endif // LOAD_FILES_H


