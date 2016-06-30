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
    //filename << "../Visualisation_heading/QTable/QTable.txt";
    filename << "../Visualisation_heading/QTable/Qtable2016-06-30_10:24:02/QTable.txt";

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
        states.push_back(vec2str2(i,2));
        actions.push_back(i[9]);
        scores.push_back(i[10]);
    }

    std::unordered_map<std::string, ActionScoreMap> Qtable;

    for(unsigned i = 0; i < states.size(); i+=3)
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

std::vector<std::vector<std::vector<double> > >Load::loadTransitionMatrix()
{

    std::ifstream myfile("../Visualisation_heading/TransitionPM/TPM0.txt");

    // new lines will be skipped unless we stop it from happening:
    myfile.unsetf(std::ios_base::skipws);

    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = std::count(
                std::istream_iterator<char>(myfile),
                std::istream_iterator<char>(),
                '\n');

    std::vector<std::vector<std::vector<double> > > transistionProbabilityMatrix
            (line_count, std::vector<std::vector<double> > (line_count, std::vector<double> (3,0)));
    std::vector<std::vector<double> > values;

    for(int count = 0; count < 3; count++)
    {
        values.resize(0);
        std::stringstream filename;
        filename << "../Visualisation_heading/TransitionPM/TPM" << count << ".txt";
        std::ifstream inFile;
        inFile.open(filename.str());

        if(!inFile.is_open())
        {
            std::cout << "LOAD: failed to open file." << "\n";
        }



        for (std::string line; std::getline(inFile, line); )
        {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream in(line);
            values.push_back(
                        std::vector<double>(std::istream_iterator<double>(in),
                                            std::istream_iterator<double>()));
        }

        for(unsigned i = 0; i < (values.size() - 1); i ++)
        {
            for(unsigned j = 0; j < values.size(); j++)
            {
                transistionProbabilityMatrix[i][j][count] = values[i][j];
            }
        }

        inFile.close();
    }

    return transistionProbabilityMatrix;
}

std::vector<std::vector<std::vector<int> > > Load::loadTransitionMatrix_discrete_distribution()
{
    //std::ifstream myfile("../Visualisation_heading/TransitionPM/TPM_discrete_dis0.txt");
    std::ifstream myfile("../Visualisation_heading/TPMfolder/TPM2016-06-30_10:39:36/TPM_count0.txt");

    // new lines will be skipped unless we stop it from happening:
    myfile.unsetf(std::ios_base::skipws);

    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = std::count(
                std::istream_iterator<char>(myfile),
                std::istream_iterator<char>(),
                '\n');

    std::vector<std::vector<std::vector<int> > > transistionProbabilityMatrix
            (line_count, std::vector<std::vector<int> > (line_count + 1, std::vector<int> (3,0)));
            //(line_count, std::vector<std::vector<int> > (line_count, std::vector<int> (3,0)));
    std::vector<std::vector<int> > values;

    for(int count = 0; count < 3; count++)
    {
        values.resize(0);
        std::stringstream filename;

        filename << "../Visualisation_heading/TPMfolder/TPM2016-06-30_10:39:36/TPM_count" << count << ".txt";
        //filename << "../Visualisation_heading/TransitionPM/TPM_discrete_dis" << count << ".txt";
        std::ifstream inFile;
        inFile.open(filename.str());

        if(!inFile.is_open())
        {
            std::cout << "LOAD: failed to open file." << "\n";
        }



        for (std::string line; std::getline(inFile, line); )
        {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream in(line);
            values.push_back(
                        std::vector<int>(std::istream_iterator<int>(in),
                                            std::istream_iterator<int>()));
        }


        int sum = 0;

        for (int i = 0; i < (values.size() ); i++)
        {
            for(int j = 0; ( j < values.size()  ); j++)
            {
                sum = sum + values[i][j];
            }
        values[i].push_back(sum);
        sum = 0;

        }



        for(unsigned i = 0; i < (values.size()); i ++)
        {
            for(unsigned j = 0; j < values.size() + 1; j++)
            {
                transistionProbabilityMatrix[i][j][count] = values[i][j];
            }
        }

        inFile.close();
    }

    return transistionProbabilityMatrix;
}

std::unordered_map<std::string, int> Load::loadString2Int()
{
    std::stringstream filename;
    //filename << "../Visualisation_heading/string2int/str2int.txt";
    filename << "../Visualisation_heading/QTable/Qconversion2016-06-28_13:04:22/Qconversion.txt";
    std::ifstream inFile;
    inFile.open(filename.str());

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

    std::vector<unsigned> identifier;
    std::vector<std::string> states;

    for(std::vector<double> &i : values)
    {
        states.push_back(vec2str2(i,1));
        identifier.push_back(i[9]);
    }

    inFile.close();

    std::unordered_map<std::string, int> string2intconversion;


    for(unsigned i = 0; i < values.size() ; i++)
    {
        string2intconversion[states[i]] = identifier[i];
    }

    return string2intconversion;

}


