#include <algorithm>    // std::find
#include <random>       // random
#include <mutex>


#include "khepera_test.h"
#include "load_files.h"
#include "transitionmatrix.h"



#include "bt_test_gp_kirk.h"
#include "../EvolutionaryLearning/GP.h"
#include "../EvolutionaryLearning/test_common.h"
#include "../BT/btFile.h"


//#define Q_LEARNING

using namespace BT;
using namespace GP;

struct run_gen_thread{
    GP::citizens* population;
    //delfly_sim_settings *settings;
    //room* myroom;
    int threadnr;
    size_t k_run;
    const char *log;
};

size_t next;
std::mutex mtx;

void Khepera_T::runKhepera_wiht_GP(int totalsteps, std::string start, blackboard *p_BLKB, int number_of_gen)
{



    // set up new file directory
    std::stringstream workingfolder;
    workingfolder<<"../BTRuns/"<<currentDateTime()<<"/";
    create_directory(workingfolder.str());


    std::stringstream workingfolder1, filename;
    workingfolder1 << "../BTstats/";
    create_directory(workingfolder1.str());
    filename<<workingfolder1.str()<<"statistics_" << currentDateTime() << ".txt";
    std::string statsFileName(filename.str());



    // 1. Initialize Settings()

    // define globals
    size_t generation = 0;
    size_t k_generations = number_of_gen;

    // define GP parameters
    size_t k_population = 100;       // currently need at least 5, need to include a check to force this
    size_t max_runs = 2;
    //size_t run = 0;

    // 2. Initialize Tree_population()
    citizens population;
    citizens archive;
    std::vector<citizen*> world_pop;

    // number of objective functions and behaviour metrics must be defined here!
    for (size_t i = 0; i < k_population; i++)
        population.push_back( new citizen(1, 1) );

    //std::vector<double> avg_fitness(max_runs);

    // 3. runKhepera_test() for tree

    for (generation = 0; generation < k_generations; generation++)
    {
        std::cout << "Evaluating generation: " << generation << "\n";
        world_pop.clear();
        world_pop.insert( world_pop.end(), archive.begin(), archive.end() );
        world_pop.insert( world_pop.end(), population.begin(), population.end() );

        // Run population
        run_gen((citizens*)&population, max_runs, generation);

        // Save statistics
        std::sort(world_pop.begin(), world_pop.end(), sort_mean<citizen>);
        save_statistics((citizens*)&world_pop, generation, statsFileName);

        // 5. Procreate BTs
        procreate( &archive, &population );   // check this, now procreating and doing nothing with last pop
    }




    std::sort(archive.begin(), archive.end(), sort_mean<citizen>);
    composite* tree;
    tree = archive.front()->BT;
    std::stringstream workingfolder3, filename3;
//    workingfolder3 << "../BT_saves/";
//    create_directory(workingfolder3.str());
    filename3 << "../../BT_saves/BT_" << currentDateTime() << ".txt";

    saveFile( filename3.str() , tree);



}



void Khepera_T::run_gen(citizens *population, size_t runs, int generation)
{

    int t_end = 100;
    int t;
    composite* tree;
    int action;
    double score_total;
    std::string state_init = "1,1,1,3,1,1,1,1,0";
    std::string state;

     for(size_t i = 0; i < population->size(); i++)
    {
         score_total = 0.;
         tree = population->at(i)->BT;

        for(size_t j = 0; j < runs; j++) // <- Run same tree multiple times to get good score
        {
            // add place holders for new run
            if(population->at(i)->VF.front().size() < runs){
                for (size_t k = 0; k < population->at(i)->VF.size(); k++)
                    population->at(i)->VF[k].push_back(0.);
            }
            else {
                continue;       // don't retest individuals
            }

            t = 0;
            state = state_init;
            score_total = 0.;
            while(t < t_end)
            {
                // char to num
                BLKB->set("sensor0", state.at(0) - 48);
                BLKB->set("sensor1", state.at(2) - 48);
                BLKB->set("sensor2", state.at(4) - 48);
                BLKB->set("sensor3", state.at(6) - 48);
                BLKB->set("sensor4", state.at(8) - 48);
                BLKB->set("sensor5", state.at(10) - 48);
                BLKB->set("sensor6", state.at(12) - 48);
                BLKB->set("sensor7", state.at(14) - 48);

                tree->update(BLKB);
        //        sol_met->chooseAction(p_BLKB);

                action = static_cast<int> (BLKB->get("action") ); // read action from blackboard



                ActionScoreMap a = this->Qtable[state];
                Score score_max = 0;
                int action_best;

                for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
                {
                    if(it == a.begin())
                    {
                        score_max = it->second;
                        action_best = it->first;
                    }

                    if(it->second > score_max)  // NOTE: In case two same scores, returns first
                    {
                        score_max = it->second;
                        action_best = it->first;
                    }
                }


                // Fitness - if action selected is same as greedy-policy selection +1, otherwise -1;
                if(action == action_best)
                {
                    score_total = score_total + 1;
                }
                else
                {

                }



//                std::cout<<state<<std::endl;
//                printf("action: %d \n ",action);
                // get new state

                state = transition(state, action);

                // get value new state
                //score_total += Qtable[state][action];

                t++;
            }   // t < tend

            if (i % 50 == 0)
            std::cout << "KHEPERA_TEST:: the score is: " << score_total << "\n";

            population->at(i)->VF[0][j] =  score_total/100;		// size

//            if (population->at(i)->VF[0][j] > 0.80)
//            {
//                population->at(i)->VF[0][j] = 1 - ( (int)getNodeCount(population->at(i)->BT) - 20)  / 200.;
//                population->at(i)->VF[0][j] = limit(population->at(i)->VF[0][i], 0, 1);
//            }

            population->at(i)->comp_fit_stats();	// needs to be run for every simulation run!

        }   // run

    }   // population size

}

void Khepera_T::runKhepera_test(int totalsteps, std::string start)
{

//    TransitionMatrix TM1(500, 3);

    double score_total = 0;
    std::string state = start;
    std::string state_new;

    for(int steps = 0; steps < totalsteps; steps++)
    {
        // Get action from choose-method
        int action; //  = rand() % 3;

        // CHECK Q LEARNING
#ifdef Q_LEARNING
        ActionScoreMap a = this->Qtable[state];
        Score max_score;
        int best_action;

        for(std::unordered_map<int,Score>::iterator it=a.begin(); it != a.end(); it++)
        {
            if(it == a.begin())
            {
                max_score = it->second;
                best_action = static_cast<int>(it->first);
            }

            if(it->second > max_score)  // NOTE: In case two same scores, returns first
            {
                max_score = it->second;
                best_action = static_cast<int>(it->first);
            }
        }
        BLKB->set("action",best_action);
#else
        sol_met->chooseAction(BLKB);
#endif



        action = static_cast<int> (BLKB->get("action") ); // read action from blackboard
//        std::cout<<state<<std::endl;
//        printf("action: %d \n",action);

        // get new state
        state_new = transition(state, action);

        score_total += Qtable[state][action];

        // Set sensor information to BB
        BLKB->set("sensor0", state_new.at(0) - 48);
        BLKB->set("sensor1", state_new.at(2) - 48);
        BLKB->set("sensor2", state_new.at(4) - 48);
        BLKB->set("sensor3", state_new.at(6) - 48);
        BLKB->set("sensor4", state_new.at(8) - 48);
        BLKB->set("sensor5", state_new.at(10) - 48);
        BLKB->set("sensor6", state_new.at(12) - 48);
        BLKB->set("sensor7", state_new.at(14) - 48);

        state = state_new;
    }
    std::cout << "The total score is: " << score_total << std::endl;
    score_tree = score_total;
}


std::vector<int> Khepera_T::string2vec(std::string state)
{
        std::vector<int> state_vec;

        // Fill DataNumbers
        for (int i=0; i < 17; i+=2 )
        {
            char s = state.at(i);
            int int_state = s - 48 ;
            state_vec.push_back(int_state);
        }

        return state_vec;
}

std::string Khepera_T::transition(std::string state, int action)
{
    std::vector<int> discrete_distribution_vec;
    discrete_distribution_vec = getTransitions(state, action);
    double sum_of_elems = 0;

    for (int n : discrete_distribution_vec){
        sum_of_elems += n;
    }

    if(sum_of_elems != 0){
        std::string new_state = returnNextState(discrete_distribution_vec);
        //std::cout << "The new state is: " <<new_state << std::endl;
        return new_state;
    }
    else{
        //std::cout << "This transition did not happen during exploration/learning" << std::endl;
        //std::cout << "Returned a random state" << std::endl;
        //return state;
        return returnRandomState();
    }
}

std::vector<int> Khepera_T::getTransitions(std::string state, int action)
{
    std::vector<int> TP;
    int in_state = string2int[state];

    TP.reserve(transitionMatrix_discrete_distribution[in_state].size());

    for(unsigned i = 0; i <  (transitionMatrix_discrete_distribution[in_state].size()); i++ ){
        TP.push_back(transitionMatrix_discrete_distribution[in_state][i][action]);
    }
    return TP;
}

std::string Khepera_T::returnNextState(std::vector<int> transitionVector)
{
    //std::mt19937 gen(1701);
    //std::default_random_engine generator(rand() % 100 );
    std::discrete_distribution<> distr(transitionVector.begin(), transitionVector.end());
    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), distr(generator));
    return keys[std::distance(vals.begin(), it)];
}

std::string Khepera_T::returnRandomState()
{
    return keys[(rand() % keys.size() ) - 1];
}
