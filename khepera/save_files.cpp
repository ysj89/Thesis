#include <sstream>
#include <vector>

#include "save_files.h"
#include "helpfunctions.h"
#include "../EvolutionaryLearning/test_common.h"

void Save::printAgentReward(std::vector<double> *rewardVec, std::string folder, int i)
{
    std::stringstream filename;
    filename << folder <<"reward_eps" << i << ".txt";
    //filename << "../Visualisation_heading/Reward/reward_last_eps.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVector(rewardVec, fs);
    fs.close();

}

void Save::printwallencounter(std::vector<int> *wall_vec, std::string folder, int i)
{
    std::stringstream filename;
    filename << folder <<"wall_vec_eps" << i << ".txt";
    //filename << "../Visualisation_heading/wall_vec/wall_vec.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVector(wall_vec, fs);
    fs.close();

}

void Save::printQincrement(std::vector<double> *Qincrement)
{

    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/QDelta/Qdelta"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());


    std::stringstream filename;
    //filename << "../Visualisation_heading/Qvalues/deltaQ.txt";
    filename << workingfolder.str() << "Qdelta.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVector(Qincrement, fs);
    fs.close();
}

void Save::printQvalue(std::vector<double> *Qvalues)
{

    std::stringstream filename;
    //filename << "/home/yannick_janssen/GIT/Thesis/khepera/Visualisation_heading/Qvalues/Qvalue.txt";
    filename << "../Visualisation_heading/Qvalues/Qvalue.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVector(Qvalues, fs);
    fs.close();
}

void Save::printQvaluetotal(std::vector<double> *Qvaluetotal)
{

    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/QTotal/Qtotal"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());


    std::stringstream filename;
    //filename << "../Visualisation_heading/Qvalues/Qvaluetotal.txt";
    filename << workingfolder.str() << "Qtotal.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVector(Qvaluetotal, fs);
    fs.close();
}


void Save::printAgentRewardperEpisode(std::vector<std::pair<int, double> > totalRewardVec)
{

    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/Reward_per_eps/Reward_"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());

    std::stringstream filename;
    //filename << "../Visualisation_heading/Reward_per_eps/totalreward.txt";
    filename << workingfolder.str() << "totalreward.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputVectorPair(totalRewardVec,fs);
    fs.close();
}

void Save::printAgentExploration(int episode, std::vector<std::vector<int> > &m_explorationmap)
{
    std::stringstream filename;
    filename << "../Visualisation_heading/Exploration/explore" << episode << ".txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputMatrix(m_explorationmap, fs);
    fs.close();
}

void Save::printwallAvoiding(std::vector<std::vector<int> > good_action, std::string folder)
{

    std::stringstream filename;
    //filename << "../Visualisation_heading/World/TotalWorld" << steps << ".txt";
    filename << folder <<"good_action.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
    Print::outputMatrix(good_action, fs);
    fs.close();
}

void Save::printAgentinRoom(int steps, std::vector<std::vector<double> > &m_printMap, std::string folder)
{

    std::stringstream filename;
    //filename << "../Visualisation_heading/World/TotalWorld" << steps << ".txt";
    filename << folder <<"TotalWorld" << steps << ".txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
    Print::outputMatrix(m_printMap, fs);
    fs.close();
}

void Save::printQtable(std::unordered_map<std::string, ActionScoreMap> &m_Qtable)
{

    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/QTable/Qtable"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());

    std::stringstream filename;
    //filename << "../Visualisation_heading/QTable/QTable.txt";
    filename << workingfolder.str() << "QTable.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputQTable(m_Qtable, fs);
    fs.close();
}

void Save::printTPM(std::vector<std::vector<double> > &m_TPM)
{
    std::stringstream filename;
    filename << "../Visualisation_heading/TransitionPM/TPM.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
    Print::outputMatrix(m_TPM, fs);
    fs.close();
}

void Save::printTPM3D(std::vector<std::vector<std::vector<double> > > &m_TPM, int TPM_size)
{
    std::vector<std::vector<double> > tempMatrix (TPM_size, std::vector<double>(TPM_size,0));

    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/TPMfolder/TPM"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());

    for(unsigned int a = 0; a < m_TPM[0][1].size(); a++ ) {
        for(int i = 0; i < TPM_size; i++ ) {
            for(int j = 0; j < TPM_size; j++ ) {
                tempMatrix[i][j] = m_TPM[i][j][a];
            }
        }


        std::stringstream filename;
        //filename << "../Visualisation_heading/TransitionPM/TPM" << a << ".txt";
        filename << workingfolder.str() << "TPM" << a << ".txt";
        std::ofstream fs;
        fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
        Print::outputMatrix(tempMatrix, fs);
        fs.close();
    }

    tempMatrix.clear();
}

void Save::printTPM_discrete_distribution(std::vector<std::vector<std::vector<unsigned> > > &m_TPM, int TPM_size)
{
    std::vector<std::vector<unsigned> > tempMatrix (TPM_size, std::vector<unsigned>(TPM_size,0));


    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/TPMfolder/TPM"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());

    for(unsigned int a = 0; a < m_TPM[0][1].size(); a++ ){
        for(int i = 0; i < TPM_size; i++ ){
            for(int j = 0; j < TPM_size; j++ ){
                tempMatrix[i][j] = m_TPM[i][j][a];
            }
        }

        std::stringstream filename;
        //filename << "../Visualisation_heading/TransitionPM/TPM_disc" << a << ".txt";
        filename << workingfolder.str() << "TPM_count" << a << ".txt";
        std::ofstream fs;
        fs.open(filename.str(), std::ios::out); // IOS::OUT is vervangen vs IOS::APP
        Print::outputMatrix(tempMatrix, fs);
        fs.close();

    }

    tempMatrix.clear();
}

void Save::printTPMunorderedMap(std::unordered_map<std::string, unsigned int> &m_string2intMap1)
{

    std::stringstream workingfolder;
    workingfolder << "../Visualisation_heading/Qconversion/Qconversion"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());

    std::stringstream filename;
    //filename << "../Visualisation_heading/string2int/str2int.txt";
    filename << workingfolder.str() << "Qconversion.txt";
    std::ofstream fs;
    fs.open(filename.str(), std::ios::out);
    Print::outputUMstr2int(m_string2intMap1, fs);
    fs.close();
}
