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
}




#endif // HELPFUNCTIONS_H
