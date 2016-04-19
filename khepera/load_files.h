#ifndef LOAD_FILES_H
#define LOAD_FILES_H

#include "posvec_struct.h"
struct Load
{
    std::unordered_map<std::string, ActionScoreMap> loadQtable1();
    std::vector<std::vector<std::vector<double> > > loadTransitionMatrix();
    std::unordered_map<std::string, int> loadString2Int();
};

#endif // LOAD_FILES_H


