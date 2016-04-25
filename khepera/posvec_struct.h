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

typedef std::pair<std::string, std::string> TransitionPair;

typedef std::unordered_map<int, int> TransitionProbability;


//struct pair_hash {
//    template <class T1, class T2>
//    std::size_t operator () (const std::pair<T1,T2> &p) {
//        auto h1 = std::hash<T1>{}(p.first);
//        auto h2 = std::hash<T2>{}(p.second);

//        // Mainly for demonstration purposes, i.e. works but is overly simple
//        // In the real world, use sth. like boost.hash_combine
//        return h1 ^ h2;
//    }
//};

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

template<typename T>
std::string vec2str2( std::vector<T> _vec,int cut_of, std::string sep=",")
{
    std::stringstream ss;

    for(typename std::vector<T>::iterator it = _vec.begin() ; it != (_vec.end()-cut_of) ; it++)
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
