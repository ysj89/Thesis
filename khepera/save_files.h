#ifndef SAVE_FILES_H
#define SAVE_FILES_H

#include <unordered_map>
#include "helpfunctions.h"

struct Save
{
    void printAgentReward(std::vector<double> *rewardVec, std::string folder, int i);
    void printwallencounter(std::vector<int> *wall_vec, std::string folder, int i);
    void printQincrement(std::vector<double> *Qincrement);
    void printQvalue(std::vector<double> *Qvalues);
    void printQvaluetotal(std::vector<double> *Qvaluetotal);

    void printAgentRewardperEpisode(std::vector<std::pair<int,double>> totalRewardVec);
    void printAgentExploration(int episode, std::string folder, std::vector<std::vector<int> > &m_explorationmap);
    void printwallAvoiding(std::vector<std::vector<int> > good_action, std::string folder);

    void printAgentinRoom(int steps, std::vector<std::vector<double> > &m_printMap, std::string folder);
    void printQtable(std::unordered_map<std::string, ActionScoreMap> &m_Qtable);
    void printTPM(std::vector<std::vector<double> > & m_TPM);
    void printTPM3D(std::vector<std::vector<std::vector<double> > > & m_TPM, int TPM_size);
    void printTPM_discrete_distribution(std::vector<std::vector<std::vector<unsigned> > > &m_TPM, int TPM_size);

    void printTPMunorderedMap(std::unordered_map<std::string, unsigned int> &m_string2intMap1);

};

#endif // SAVE_FILES_H
