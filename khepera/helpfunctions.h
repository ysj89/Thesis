#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H


#include <iostream>
#include <fstream>
#include <vector>

namespace Print
{

template <typename T>

void outputMatrix(std::vector<std::vector<T> > matrix, std::ostream& stream, char seperator='\t')
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





}




#endif // HELPFUNCTIONS_H
