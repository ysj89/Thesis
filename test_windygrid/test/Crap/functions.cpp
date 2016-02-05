#include <iostream>
#include <vector>
#include <algorithm>

#include "windygridworld.h"
#include "agent.h"
#include "functions.h"




using std::vector;
using namespace std;
using namespace functions;

double functions::maxIndexArray(vector<vector<vector<double> > > &array3D)
{

int max;
int index_x;
//int index_y;
//int index_z;

max = array3D[0][0][0];

vector<int> index(3);

    for(unsigned int i=0; i< array3D.size(); i++)
    {
       for(unsigned int j=0; j < array3D[i].size(); j++)
       {
           for(unsigned int k = 0; k < array3D[i][j].size(); k++)
           {
               if(array3D[i][j][k] > max)
               {
                    max = array3D[i][j][k];
                    index_x = i;
//                    index_y = j;
//                    index_z = k;
               }
           }
       }
    }
/*
cout << "The maximum value is " << array3D[index_x][index_y][index_z] << "\n";
cout << "and its index is (x y z) : ";

for(unsigned int i=0; i<index.size(); ++i)
{
cout << index[i] << ' ';
}
cout << "\n";
*/
    return index_x;
}

int functions::getMaxPos(vector<double > &vector)
{
    int max = 0;
    int max_index;

        for(unsigned int i=0; i< vector.size(); i++)
        {
            if(max<vector[i])
            {
                max = vector[i];
                max_index = i;
            }
        }
    return max_index;
}
