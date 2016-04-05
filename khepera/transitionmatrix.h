#ifndef TRANSITIONMATRIX_H
#define TRANSITIONMATRIX_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>


class TransitionMatrix
{
public:
    TransitionMatrix();

    // Main interface
    int get(std::string x1, std::string x2);
    void increment(std::string x1, std::string x2);

    // std::vector<std::pair<std::string,int> getVecX2(std::string x1)

    // string2intMap interface
    unsigned getIndexFromString1(std::string s);
    unsigned getIndexFromString2(std::string s);

private:
    std::unordered_map<std::string, unsigned> string2intMap1;
    std::unordered_map<std::string, unsigned> string2intMap2;
    unsigned currentStringIndex1;
    unsigned currentStringIndex2;

    int* tm;


};

#endif // TRANSITIONMATRIX_H
