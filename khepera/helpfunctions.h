#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

#include "posvec_struct.h"

inline static double limit(double val, double lower, double upper)
{
    if (val > upper)
        val = upper;
    else if (val < lower)
        val = lower;

    return val;
}


namespace Print
{

void outputQTable(std::unordered_map<std::string, ActionScoreMap> Qtable, std::ostream& stream, char seperatpr =',');
void outputVectorPair(std::vector< std::pair<int,double> > VectorPair, std::ostream& stream, char seperator = '\t');
void outputUMstr2int(std::unordered_map<std::string, unsigned int> UM, std::ostream& stream, char seperator = ',');

template <typename T>
void outputMatrix(std::vector<std::vector<T> > &matrix, std::ostream& stream, char seperator=' ') // changed seperator
{
    for(std::vector<T> &v : matrix)
    {
        for(T &i : v)
        {
            stream << i << seperator;
        }
        stream << std::endl;
    }
}

template <typename T>
void p_outputMatrix(std::vector<std::vector<T> > *matrix, std::ostream& stream, char seperator='\t')
{
    for(std::vector<T> &v : *matrix)
    {
        for(T &i : v)
        {
            stream << i << seperator;
        }
        stream << std::endl;
    }
}


template <typename T>
void outputVector(std::vector<T> *vector, std::ostream& stream)
{
    for(T &v : *vector)
    {
        stream << v << std::endl;
    }
}


template <typename T>
void outputDouble(T reward_double, std::ostream& stream)
{

    stream << reward_double;

    stream << std::endl;
}

template <typename T, typename Y>
void outputTwoValues(T first, Y second, std::ostream& stream)
{

    stream << first << "\t" << second ;

    stream << std::endl;
}


inline static double limit(double val, double lower, double upper)
{
    if (val > upper)
        val = upper;
    else if (val < lower)
        val = lower;

    return val;
}


}


#endif // HELPFUNCTIONS_H
