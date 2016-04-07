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

void Save::printTPM3D(std::vector<std::vector<std::vector<double> > > &m_TPM)
{
    std::vector<std::vector<double> > tempMatrix (m_TPM[1].size(), std::vector<double>(m_TPM[2].size(),0));

    for(int a = 0; a < m_TPM[0][1].size(); a++ )
    {
        for(unsigned int i = 0; i < m_TPM[0].size(); i++ )
        {
            for(unsigned int j = 0; j < m_TPM[1].size(); j++ )
            {
                tempMatrix[i][j] = m_TPM[i][j][a];
            }
        }

        std::stringstream filename;
        filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/TransitionPM/TPM" << a << ".txt";
        std::ofstream fs;
        fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
        Print::outputMatrix(tempMatrix, fs);
        fs.close();

    }

    tempMatrix.clear();
}
