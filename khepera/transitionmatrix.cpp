//#include "iostream"
#include "transitionmatrix.h"


TransitionMatrix::TransitionMatrix(unsigned size_tm, unsigned num_of_actions) :
    currentStringIndex1(0),
    currentStringIndex2(0)
{   // Unsigned vs Int
    transitionMatrix = std::vector<std::vector<std::vector<unsigned> > > {size_tm,std::vector<std::vector<unsigned> > (size_tm, std::vector<unsigned>(num_of_actions,0))};
    sum_of_row_vec = std::vector<std::vector<int> >{size_tm, std::vector<int>(num_of_actions,0)};
    TPM = std::vector<std::vector<double> > {size_tm, std::vector<double>(size_tm,0)};
    TPM2 = std::vector<std::vector<std::vector<double> > >{size_tm, std::vector<std::vector<double> >(size_tm,std::vector<double>(num_of_actions,0))};
}

//void TransitionMatrix::increment(std::string x1, std::string x2)
void TransitionMatrix::increment(StateVec state_1, StateVec state_2, int action)
{
    std::string x1 = vec2str(state_1);
    std::string x2 = vec2str(state_2);

    unsigned i1 = getIndexFromString1(x1);
    unsigned i2 = getIndexFromString1(x2);

    transitionMatrix[i1][i2][action] = ++transitionMatrix[i1][i2][action];
}

void TransitionMatrix::sumTransitions(unsigned size_tm, int num_of_action)
{
    for(unsigned int a; a < num_of_action; a++)
    {
        for(unsigned int i = 0; i < size_tm; i++ )
        {
            for(unsigned int j = 0; j < size_tm; j++ )
            {
                sum_of_row_vec[i][a] = sum_of_row_vec[i][a] + transitionMatrix[i][j][a];
            }
        }
    }
}

void TransitionMatrix::calculateTPM(unsigned size_tm, int num_of_action)
{
    sumTransitions(size_tm, num_of_action);

    for(unsigned a = 0; a < num_of_action; a++)
    {
        for(unsigned int i = 0; i < size_tm; i++ )
        {
            for(unsigned int j = 0; j< size_tm; j++ )
            {
                if(sum_of_row_vec[i][a] == 0)
                {
                    TPM2[i][j][a] = 0;
                }
                else
                {
                    TPM2[i][j][a] = transitionMatrix[i][j][a] / (double) sum_of_row_vec[i][a];
                }
            }
        }
    }
}

//void TransitionMatrix::calculatePTM(unsigned size_tm)
//{

//    sumTransitions(size_tm);

//    for(unsigned int i = 0; i < size_tm; i++ )
//    {
//        for(unsigned int j = 0; j< size_tm; j++ )
//        {
//            if(sum_of_row_vec[i] == 0)
//            {
//                TPM[i][j] = 0;
//            }
//            else
//            {
//                TPM[i][j] = transitionMatrix[i][j] / (double) sum_of_row_vec[i];
//            }
//        }
//    }
//}



unsigned TransitionMatrix::getIndexFromString1(std::string s)
{
    if(string2intMap1.find(s) == string2intMap1.end())
    {
        string2intMap1[s] = currentStringIndex1++;
    }
    return string2intMap1[s];
}

