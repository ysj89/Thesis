#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "load_files.h"



void Load::loadQtable1()
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/QTable/QTable.txt";
    std::ifstream inFile;
    inFile.open(filename.str());
    std::string word;

    if(!inFile.is_open()){
        std::cout << "LOAD: failed to open file." << "\n";
    }

    while( getline(inFile, word, ',' ))
    {
        std::cout << word << "\n";
    }


    inFile.close();

}
