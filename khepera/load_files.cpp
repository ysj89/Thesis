#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
//#include <sstream>
//#include <unordered_map>

#include "load_files.h"
#include "posvec_struct.h"

std::unordered_map<std::string, ActionScoreMap> Load::loadQtable1()
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/QTable/QTable.txt";
    std::ifstream inFile;
    inFile.open(filename.str());
//    std::string word;

    if(!inFile.is_open()){
        std::cout << "LOAD: failed to open file." << "\n";
    }
    std::vector<std::vector<double> > values;
    for (std::string line; std::getline(inFile, line); )
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values.push_back(
            std::vector<double>(std::istream_iterator<double>(in),
                                std::istream_iterator<double>()));
    }

    std::vector<std::string> states;
    std::vector<int> actions;
    std::vector<Score> scores;

    for(std::vector<double> &i : values)
    {
        states.push_back(vec2str2(i));
        actions.push_back(i[9]);
        scores.push_back(i[10]);
    }

    std::unordered_map<std::string, ActionScoreMap> Qtable;

    for(int i = 0; i < states.size(); i+=3)
    {

        ActionScoreMap a;
        for(int j = 0; j < 3 ; j++)
        {
            a[actions[i+j]] = scores[i+j];
        }

        Qtable[states[i]] = a;
    }


     if (!inFile.eof())
     {
       std::cerr << "Fooey!\n";
     }

    inFile.close();

    return Qtable;
}

std::vector<std::vector<double> > Load::loadTransitionMatrix()
{

    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/TransitionPM/TPM1.txt";
    std::ifstream inFile;
    inFile.open(filename.str());


    if(!inFile.is_open())
    {
        std::cout << "LOAD: failed to open file." << "\n";
    }

    std::vector<std::vector<double> > values;
    for (std::string line; std::getline(inFile, line); )
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values.push_back(
            std::vector<double>(std::istream_iterator<double>(in),
                                std::istream_iterator<double>()));
    }

    std::vector<std::vector<std::vector<double> > > transistionProbabilityMatrix
            (values.size(), std::vector<std::vector<double> > (values.size(), std::vector<double> (3,0)));

    for(int i = 0; i < values.size(); i ++)
    {
        for(int j = 0; j < values.size(); j++)
        {
            transistionProbabilityMatrix[i][j][0] = values[i][j];
        }
    }



    return values;


}
