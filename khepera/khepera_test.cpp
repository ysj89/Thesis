#include <algorithm>    // std::find
#include <random>       // random
#include <mutex>

#include "khepera_test.h"
#include "load_files.h"
#include "transitionmatrix.h"

#include "bt_test_gp_kirk.h"
#include "../EvolutionaryLearning/GP.h"



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





void Khepera_T::runKhepera_wiht_GP(int totalsteps, std::string start, blackboard *p_BLKB)
{


    // 1. Initialize Settings()


    // define globals
    const double t_end = 150.;
    size_t generation = 0;
    size_t k_generations = 50;

    // define GP parameters
    size_t k_population = 100;       // currently need at least 5, need to include a check to force this
    size_t max_runs = 5;
    size_t run = 0;


    // 2. Initialize Tree_population()
    citizens population;
    citizens archive;
    std::vector<citizen*> world_pop;

    // number of objective functions and behaviour metrics must be defined here!
    for (size_t i= 0; i < k_population; i++)
        population.push_back( new citizen(1, 1) );

    std::vector<double> avg_fitness;


    // 3. runKhepera_test() for tree

    for (generation = 0; generation < k_generations; generation++)
    {
        world_pop.clear();
        world_pop.insert( world_pop.end(), archive.begin(), archive.end() );
        world_pop.insert( world_pop.end(), population.begin(), population.end() );


        run_gen((citizens*)&world_pop, max_runs);





        // 4. Store BT_Q_value
        //thread_data->population->at(j)->VF[0][1] = score_tree;


        // 5. Procreate BTs
    }






}

void Khepera_T::run_gen(citizens *population, size_t k_run)
{
    int t_end = 150;
    int t;
    composite* tree;
    int action;
    double score_total;
    std::string state = "1,1,1,3,1,1,1,1,0";
    std::string state_new;

     for(size_t i = 0; i < population->size(); i++)
    {



         double score = 0;
         double score_av = 0;

        for(size_t j = 0; j < k_run; j++) // <- Run same tree multiple times to get good score
        {
            t = 0;

            while(t < t_end)
            {

            tree = population->at(i)->BT;

            tree->update(BLKB);
    //        sol_met->chooseAction(p_BLKB);



            action = static_cast<int> (BLKB->get("action") ); // read action from blackboard

            // get new state
            state_new = transition(state, action);

            // get value new state
            ActionScoreMap as;
            as = Qtable[state_new];


            score = as[action];
            score_total = score_total + score;

            // convert state back to vector and put on BB
            state_vec_temp = string2vec(state_new);
            BLKB->set("sensor0", state_vec_temp[0]);
            BLKB->set("sensor1", state_vec_temp[1]);
            BLKB->set("sensor2", state_vec_temp[2]);
            BLKB->set("sensor3", state_vec_temp[3]);
            BLKB->set("sensor4", state_vec_temp[4]);
            BLKB->set("sensor5", state_vec_temp[5]);
            BLKB->set("sensor6", state_vec_temp[6]);
            BLKB->set("sensor7", state_vec_temp[7]);


            state = state_new;
            t++;

            }
            score_av = score_total / k_run;

            std::cout << "KHEPERA_TEST:: the average score is: " << score_av << "\n";
            population->at(j)->VF[0][0] = score_av;		// size


//        score_tree = score_tree/k_run

        }

    }




        // run tree x-times
        // store tree _score



}

void Khepera_T::runKhepera_test(int totalsteps, std::string start)
{

    TransitionMatrix TM1(500, 3);

    double score_total;
    std::string state = start;
    std::string state_new;

    for(int steps = 0; steps < totalsteps; steps++)
    {
        // Get action from choose-method
        int action; //  = rand() % 3;

        sol_met->chooseAction(BLKB);
        action = static_cast<int> (BLKB->get("action") ); // read action from blackboard

        // get new state
        state_new = transition(state, action);

        // get value new state
        ActionScoreMap as;
        as = Qtable[state_new];

        double score;
        score = as[action];
        score_total = score_total + score;

        // convert state back to vector and put on BB
        state_vec_temp = string2vec(state_new);
        BLKB->set("sensor0", state_vec_temp[0]);
        BLKB->set("sensor1", state_vec_temp[1]);
        BLKB->set("sensor2", state_vec_temp[2]);
        BLKB->set("sensor3", state_vec_temp[3]);
        BLKB->set("sensor4", state_vec_temp[4]);
        BLKB->set("sensor5", state_vec_temp[5]);
        BLKB->set("sensor6", state_vec_temp[6]);
        BLKB->set("sensor7", state_vec_temp[7]);

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

    for (int n : discrete_distribution_vec)
    {
        sum_of_elems += n;
    }

    if(sum_of_elems != 0)
    {

        std::string new_state = returnNextState(discrete_distribution_vec);
        std::cout << "The new state is: " <<new_state << std::endl;
        return new_state;
    }
    else
    {
        std::cout << "This transition did not happen during exploration/learning" << std::endl;
        return state;
    }
}

std::vector<int> Khepera_T::getTransitions(std::string state, int action)
{
    std::vector<int> TP;
    TP.reserve(string2int.size());
    int in_state = string2int[state];

    for(unsigned i = 0; i <  (transitionMatrix_discrete_distribution[1].size()); i++ )
    {
        TP.push_back(transitionMatrix_discrete_distribution[in_state][i][action]);
    }

    return TP;
}

std::string Khepera_T::returnNextState(std::vector<int> transitionVector)
{
    //std::mt19937 gen(1701);
    std::default_random_engine generator(seed1);

    std::discrete_distribution<> distr(transitionVector.begin(), transitionVector.end());

    unsigned next_state = distr(generator);

    std::vector<int>::iterator it = std::find(vals.begin(), vals.end(), next_state);
    int pos = std::distance(vals.begin(), it);

    std::string new_state = keys[pos];

    return new_state;
}


