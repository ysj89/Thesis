#ifndef POSVEC_STRUCT_H
#define POSVEC_STRUCT_H

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <unordered_map>


typedef std::vector<int> StateVec;

typedef double Score;

typedef std::unordered_map<int, Score> ActionScoreMap;

typedef enum Action
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
}Action;

struct PosVec
{
        int x, y;
};


template<typename T>
std::string vec2str( std::vector<T> _vec, std::string sep=",")
{
    std::stringstream ss;

    for(typename std::vector<T>::iterator it = _vec.begin() ; it != _vec.end() ; it++)
    {
        if(it != _vec.begin() )
        {
            ss << sep;
        }
            ss << *it;
    }
    return ss.str();
}



#endif // POSVEC_STRUCT_H
