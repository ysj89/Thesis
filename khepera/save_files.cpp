#include <sstream>
#include <vector>

#include "save_files.h"
#include "helpfunctions.h"


void Save::printAgentReward(std::vector<double> *rewardVec)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/Reward/reward_last_eps.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVector(rewardVec, fs);
    fs.close();

}

void Save::printAgentRewardperEpisode(std::vector<std::pair<int, double> > totalRewardVec)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/Reward_per_eps/totalreward.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVectorPair(totalRewardVec,fs);
    fs.close();
}

void Save::printAgentExploration(int episode, std::vector<std::vector<int> > &m_explorationmap)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/Exploration/explore" << episode << ".txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputMatrix(m_explorationmap, fs);
    fs.close();
}

void Save::printAgentinRoom(int steps, std::vector<std::vector<double> > &m_printMap)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/World/TotalWorld" << steps << ".txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
    Print::outputMatrix(m_printMap, fs);
    fs.close();
}

void Save::printQtable(std::unordered_map<std::string, ActionScoreMap> &m_Qtable)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/QTable/QTable.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputQTable(m_Qtable, fs);
    fs.close();
}

void Save::printTPM(std::vector<std::vector<double> > &m_TPM)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/TransitionPM/TPM.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
    Print::outputMatrix(m_TPM, fs);
    fs.close();
}

void Save::printTPM3D(std::vector<std::vector<std::vector<double> > > &m_TPM, int TPM_size)
{
    std::vector<std::vector<double> > tempMatrix (TPM_size, std::vector<double>(TPM_size,0));

    for(unsigned int a = 0; a < m_TPM[0][1].size(); a++ )
    {
        for(int i = 0; i < TPM_size; i++ )
        {
            for(int j = 0; j < TPM_size; j++ )
            {
                tempMatrix[i][j] = m_TPM[i][j][a];
            }
        }

        std::stringstream filename;
        filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/TransitionPM/TPM" << a + 1 << ".txt";
        std::ofstream fs;
        fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
        Print::outputMatrix(tempMatrix, fs);
        fs.close();

    }

    tempMatrix.clear();
}

void Save::printTPMunorderedMap(std::unordered_map<std::string, unsigned int> &m_string2intMap1)
{
    std::stringstream filename;
    filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/string2int/str2int.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputUMstr2int(m_string2intMap1, fs);
    fs.close();
}
