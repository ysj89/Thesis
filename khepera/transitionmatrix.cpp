

//TransitionMatrix::TransitionMatrix() :
//    currentStringIndex1(0),
//    currentStringIndex2(0)
//{

//}



//void TransitionMatrix::increment(std::string x1, std::string x2)
//{
//    unsigned i1 = getIndexFromString1(x1);
//    unsigned i2 = getIndexFromString2(x2);

//    if(tm.size() <= i1) {
//        tm.push_back(std::vector<int>(1, 1));
//        ++tm[i1][i2];
//    } else {
//        // add value, and set to 1
//    }
//}

//unsigned TransitionMatrix::getIndexFromString1(std::string s)
//{
//    if(string2intMap1.find(s) == string2intMap1.end())
//    {
//        string2intMap1[s] = currentStringIndex1++;
//    }
//    return string2intMap1[s];
//}

//unsigned TransitionMatrix::getIndexFromString2(std::string s)
//{
//    if(string2intMap2.find(s) == string2intMap2.end())
//    {
//        string2intMap2[s] = currentStringIndex2++;
//    }
//    return string2intMap2[s];
//}

//#include "transitionmatrix.h"
