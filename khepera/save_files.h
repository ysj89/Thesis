#ifndef SAVE_FILES_H
#define SAVE_FILES_H

#include <unordered_map>

#include "helpfunctions.h"

struct Save
{
    void printAgentReward(std::vector<double> *rewardVec);
    void printAgentRewardperEpisode(std::vector<std::pair<int,double>> totalRewardVec);
    void printAgentExploration(int episode, std::vector<std::vector<int> > &m_explorationmap);
    void printAgentinRoom(int steps, std::vector<std::vector<double> > &m_printMap);
    void printQtable(std::unordered_map<std::string, ActionScoreMap> &m_Qtable);
};

#endif // SAVE_FILES_H
