#ifndef POSVEC_STRUCT_H
#define POSVEC_STRUCT_H

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <unordered_map>

struct PosVec
{
        int x, y;
};

typedef std::vector<int> StateVec;

typedef enum Action
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    MAX_ACTIONS
}Action;


typedef double Score;

typedef std::unordered_map<int, Score> ActionScoreMap;


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




//struct ObsState
//{
//    ObsState(std::vector<int> state_ )
//        : state_vec(state_)
//    {
//           this->index = ObsState::currentIndex++;


//    std::vector<int> state_vec;
//    std::vector<int> batt_life;
//    }

//    unsigned index;
//    static unsigned currentIndex;
//};


#endif // POSVEC_STRUCT_H
