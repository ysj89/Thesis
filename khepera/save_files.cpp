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
