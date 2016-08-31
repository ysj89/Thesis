#include <sstream>

#include "khepera_agent_heading.h"
//#include "khepera_agent.h"
#include "transitionmatrix.h"
#include "../EvolutionaryLearning/test_common.h"



int Agent_H::getAction_f()
{

    int action;
    action = sol_met->chooseAction(BLKB); // choose action and put on blackboard
    sol_met_test->chooseAction(BLKB2);
    action = static_cast<Action_heading> (BLKB->get("action") ); // read action from blackboard
    return action;

    // When running behavior tree
    //sol_met->getAction(BB)

}

void Agent_H::performAction(int num_episode, int current_episode)
{
    old_pos = current_pos;
    old_state = current_state;
    reward = 0;

    action = static_cast<Action_heading> ( getAction_f() ) ;

//    epsilon = .5 * (( num_episode / 100.)  + 1. ) / ( (num_episode / 100. ) + current_episode) ;

//    if( ((rand()% 100 + 1 ) / 100) > (1-epsilon))
//    {

//        if(action == 0)
//        {
//            action = static_cast<Action_heading> (rand()%2 + 1 ) ;
//            BLKB->set("action",action);
//        }
//        if(action == 1)
//        {
//            int action_rand = rand()%2;
//            if(action_rand == 1)
//            {
//                action_rand = 2;
//            }
//            action = static_cast<Action_heading> (action_rand) ;
//            BLKB->set("action",action);
//        }
//        if(action == 2)
//        {
//            action = static_cast<Action_heading> (rand()%2 ) ;
//            BLKB->set("action",action);
//        }
//    }

    // Perform action
    switch(action)
    {
    case TURN_RIGHT:    // 0
        head = static_cast<int>(heading);
        head_new = head + 1;
        if(head_new > 3)
        {
            head_new = 0;
        }
        heading = static_cast<Heading>(head_new);
        reward = -1;
        break;
    case TURN_LEFT:     // 1
        head = static_cast<int>(heading);
        head_new = head - 1;

        if(head_new < 0)
        {
            head_new = 3;
        }
        heading = static_cast<Heading>(head_new);
        reward = -1;
        break;

    case MOVE_FORWARD: // 2

        if(heading == NORTH)
            current_pos.x -= 1;
        if(heading == EAST)
            current_pos.y += 1;
        if(heading == SOUTH)
            current_pos.x += 1;
        if(heading == WEST)
            current_pos.y -= 1;

        //                reward = -1;
        break;


    default:
        std::cout << "\n Class:Agent :: Perform Action not implemented \n" ;
    }

    // Wall check
    if(m_Room->worldMap[current_pos.x][current_pos.y] == 0) // NOTE: Agent hit a wall, returns to old position
    {
        current_pos = old_pos;
        reward = -10;
    }
    if(m_Room->worldMap[current_pos.x][current_pos.y] == 3) // NOTE: Agent found trash, automatically cleans it and picks it up
    {
        reward = 20;
        m_Room->worldMap[current_pos.x][current_pos.y] = 1;

        spawnApple(rand() % m_Room->x_size, rand() % m_Room->y_size);
    }

    // State

    switch(heading)
    {
    case NORTH: // 0

        sensor0x = current_pos.x - 4;
        sensor0y = current_pos.y;
        sensor1x = current_pos.x - 3;
        sensor1y = current_pos.y    ;
        sensor2x = current_pos.x - 2;
        sensor2y = current_pos.y    ;
        sensor3x = current_pos.x - 1;
        sensor3y = current_pos.y    ;

        checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);

        current_state[4] = m_Room->worldMap[current_pos.x - 1][current_pos.y + 1];
        current_state[5] = m_Room->worldMap[current_pos.x ][current_pos.y + 1];
        current_state[6] = m_Room->worldMap[current_pos.x - 1 ][current_pos.y - 1];
        current_state[7] = m_Room->worldMap[current_pos.x][current_pos.y - 1];
        //current_state[8] = NORTH;

        break;
    case EAST: // 1

        sensor0x = current_pos.x;
        sensor0y = current_pos.y + 4;
        sensor1x = current_pos.x;
        sensor1y = current_pos.y + 3;
        sensor2x = current_pos.x;
        sensor2y = current_pos.y + 2;
        sensor3x = current_pos.x;
        sensor3y = current_pos.y + 1;

        checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);

        current_state[4] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
        current_state[5] = m_Room->worldMap[current_pos.x + 1][current_pos.y];
        current_state[6] = m_Room->worldMap[current_pos.x - 1][current_pos.y + 1];
        current_state[7] = m_Room->worldMap[current_pos.x - 1][current_pos.y];

        //current_state[8] = EAST;
        break;

    case SOUTH: // 2
        sensor0x = current_pos.x + 4;
        sensor0y = current_pos.y;
        sensor1x = current_pos.x + 3;
        sensor1y = current_pos.y;
        sensor2x = current_pos.x + 2;
        sensor2y = current_pos.y;
        sensor3x = current_pos.x + 1;
        sensor3y = current_pos.y;

        checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);

        current_state[4] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];
        current_state[5] = m_Room->worldMap[current_pos.x][current_pos.y - 1];
        current_state[6] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
        current_state[7] = m_Room->worldMap[current_pos.x][current_pos.y + 1];
        //current_state[8] = SOUTH;
        break;

    case WEST: // 3
        sensor0x = current_pos.x;
        sensor0y = current_pos.y - 4;
        sensor1x = current_pos.x;
        sensor1y = current_pos.y - 3;
        sensor2x = current_pos.x;
        sensor2y = current_pos.y - 2;
        sensor3x = current_pos.x;
        sensor3y = current_pos.y - 1;

        checkBlockedSensor(sensor0x, sensor0y, sensor1x, sensor1y, sensor2x, sensor2y, sensor3x, sensor3y);

        current_state[4] = m_Room->worldMap[current_pos.x - 1][current_pos.y - 1];
        current_state[5] = m_Room->worldMap[current_pos.x - 1][current_pos.y];
        current_state[6] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];
        current_state[7] = m_Room->worldMap[current_pos.x + 1][current_pos.y];

        //current_state[8] = WEST;
        break;
    }
    explorationMap[current_pos.x][current_pos.y] = (explorationMap[current_pos.x][current_pos.y] + 1 );
    rewardVec->at(steps) = reward;
    steps = steps + 1;
    totalreward = totalreward + reward;

    // Set BB information for BT
    BLKB->set("sensor0", current_state[0] );
    BLKB->set("sensor1", current_state[1] );
    BLKB->set("sensor2", current_state[2] );
    BLKB->set("sensor3", current_state[3] );
    BLKB->set("sensor4", current_state[4] );
    BLKB->set("sensor5", current_state[5] );
    BLKB->set("sensor6", current_state[6] );
    BLKB->set("sensor7", current_state[7] );
    //BLKB->set("sensor8", current_state[8] ); // sensor8 == heading



}




void Agent_H::setSensorInformation()
{
    double obserstatecolor = 4.2;
    printMap = m_Room->worldMap;
    printMap[current_pos.x][current_pos.y] = 5;

    if(heading == NORTH)
    {
        if((current_pos.x - 4 ) > 0)
        {
            if(printMap[current_pos.x - 4][current_pos.y] == 1)
            printMap[current_pos.x - 4][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x - 3][current_pos.y] == 1)
            printMap[current_pos.x - 3][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x - 2][current_pos.y] == 1)
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x - 1][current_pos.y] == 1)
                printMap[current_pos.x - 1][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x - 3 ) > 0)
        {
            if( printMap[current_pos.x - 3][current_pos.y] == 1)
            printMap[current_pos.x - 3][current_pos.y] = obserstatecolor;
            if( printMap[current_pos.x - 2][current_pos.y] == 1)
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x - 1][current_pos.y] == 1)
                printMap[current_pos.x - 1][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x - 2 ) > 0)
        {
            if (printMap[current_pos.x - 2][current_pos.y] == 1)
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x - 1][current_pos.y] == 1)
                printMap[current_pos.x - 1][current_pos.y] = obserstatecolor;
        }

        if(printMap[current_pos.x - 1][current_pos.y] == 1)
            printMap[current_pos.x - 1][current_pos.y] = obserstatecolor;


        if( printMap[current_pos.x - 1 ][current_pos.y + 1 ] == 1 )
        {
            printMap[current_pos.x - 1 ][current_pos.y + 1 ] = obserstatecolor;
        }

        if( printMap[current_pos.x ][current_pos.y + 1 ] == 1 )
        {
            printMap[current_pos.x][current_pos.y + 1 ] = obserstatecolor;
        }

        if( printMap[current_pos.x - 1 ][current_pos.y - 1 ] == 1  )
        {
            printMap[current_pos.x - 1 ][current_pos.y - 1 ] = obserstatecolor;
        }

        if( printMap[current_pos.x  ][current_pos.y - 1 ] == 1 )
        {
            printMap[current_pos.x  ][current_pos.y - 1 ] = obserstatecolor;
        }

    }
    if(heading == EAST)
    {
          if((current_pos.y + 4 ) < m_Room->y_size)
        {
            if( printMap[current_pos.x - 0][current_pos.y + 4] == 1)
            printMap[current_pos.x - 0][current_pos.y + 4] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y + 3] == 1)
            printMap[current_pos.x - 0][current_pos.y + 3] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y + 2] == 1)
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y + 1] == 1)
            printMap[current_pos.x - 0][current_pos.y + 1] = obserstatecolor;
        }
        else if((current_pos.y + 3 ) < m_Room->y_size)
        {
            if(printMap[current_pos.x - 0][current_pos.y + 3] == 1)
            printMap[current_pos.x - 0][current_pos.y + 3] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y + 2] == 1)
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y + 1] == 1)
            printMap[current_pos.x - 0][current_pos.y + 1] = obserstatecolor;
        }
        else if((current_pos.y + 2 ) < m_Room->y_size)
        {
            if(printMap[current_pos.x - 0][current_pos.y + 2] == 1)
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y + 1] == 1)
            printMap[current_pos.x - 0][current_pos.y + 1] = obserstatecolor;
        }

          if(printMap[current_pos.x - 0][current_pos.y + 1] == 1)
          printMap[current_pos.x - 0][current_pos.y + 1] = obserstatecolor;



        if( printMap[current_pos.x + 1 ][current_pos.y + 1 ] == 1 )
        {
            printMap[current_pos.x + 1 ][current_pos.y + 1 ] = obserstatecolor;
        }
        if( printMap[current_pos.x + 1 ][current_pos.y ] == 1 )
        {
            printMap[current_pos.x + 1 ][current_pos.y ] = obserstatecolor;
        }

        if( printMap[current_pos.x - 1 ][current_pos.y + 1 ] == 1 )
        {
            printMap[current_pos.x - 1 ][current_pos.y + 1 ] = obserstatecolor;
        }

        if( printMap[current_pos.x - 1 ][current_pos.y ] == 1 )
        {
            printMap[current_pos.x - 1 ][current_pos.y  ] = obserstatecolor;
        }
    }
    if(heading == SOUTH)
    {
        if((current_pos.x + 4 ) < m_Room->x_size)
        {
            if(printMap[current_pos.x + 4][current_pos.y] == 1)
            printMap[current_pos.x + 4][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x + 3][current_pos.y] = 1)
            printMap[current_pos.x + 3][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x + 2][current_pos.y] == 1)
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x + 1][current_pos.y] == 1)
            printMap[current_pos.x + 1][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x + 3 ) < m_Room->x_size)
        {
            if(printMap[current_pos.x + 3][current_pos.y] == 1)
            printMap[current_pos.x + 3][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x + 2][current_pos.y] == 1)
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x + 1][current_pos.y] == 1)
            printMap[current_pos.x + 1][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x + 2 ) < m_Room->x_size)
        {
            if(printMap[current_pos.x + 2][current_pos.y] == 1)
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
            if(printMap[current_pos.x + 1][current_pos.y] == 1)
            printMap[current_pos.x + 1][current_pos.y] = obserstatecolor;
        }

        if(printMap[current_pos.x + 1][current_pos.y] == 1)
        printMap[current_pos.x + 1][current_pos.y] = obserstatecolor;


        if( printMap[current_pos.x + 1 ][current_pos.y - 1 ] == 1 )
        {
            printMap[current_pos.x + 1 ][current_pos.y - 1] = obserstatecolor;
        }
        if( printMap[current_pos.x ][current_pos.y - 1 ] == 1 )
        {
            printMap[current_pos.x ][current_pos.y - 1] = obserstatecolor;
        }
        if( printMap[current_pos.x + 1 ][current_pos.y + 1 ] == 1 )
        {
            printMap[current_pos.x + 1 ][current_pos.y + 1] = obserstatecolor;
        }
        if( printMap[current_pos.x  ][current_pos.y + 1 ] == 1 )
        {
            printMap[current_pos.x  ][current_pos.y + 1] = obserstatecolor;
        }

    }
    if(heading == WEST) // 3
    {
        if((current_pos.y - 4 ) > 0)
        {
            if(printMap[current_pos.x - 0][current_pos.y - 4] == 1)
            printMap[current_pos.x - 0][current_pos.y - 4] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y - 3] == 1)
            printMap[current_pos.x - 0][current_pos.y - 3] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y - 2] == 1)
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y - 1] == 1)
            printMap[current_pos.x - 0][current_pos.y - 1] = obserstatecolor;
        }
        else if((current_pos.y - 3 ) > 0)
        {
            if(printMap[current_pos.x - 0][current_pos.y - 3]  == 1)
            printMap[current_pos.x - 0][current_pos.y - 3] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y - 2]  == 1)
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y - 1] == 1)
            printMap[current_pos.x - 0][current_pos.y - 1] = obserstatecolor;
        }
        else if((current_pos.y - 3 ) > 0)
        {
            if(printMap[current_pos.x - 0][current_pos.y - 2] == 1)
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
            if(printMap[current_pos.x - 0][current_pos.y - 1] == 1)
            printMap[current_pos.x - 0][current_pos.y - 1] = obserstatecolor;
        }

        if(printMap[current_pos.x - 0][current_pos.y - 1] == 1)
        printMap[current_pos.x - 0][current_pos.y - 1] = obserstatecolor;

        if( printMap[current_pos.x - 1  ][current_pos.y - 1 ] == 1 )
        {
            printMap[current_pos.x - 1 ][current_pos.y - 1] = obserstatecolor;
        }
        if( printMap[current_pos.x - 1 ][current_pos.y] == 1 )
        {
            printMap[current_pos.x - 1  ][current_pos.y] = obserstatecolor;
        }
        if( printMap[current_pos.x + 1  ][current_pos.y - 1 ] == 1 )
        {
            printMap[current_pos.x + 1  ][current_pos.y - 1] = obserstatecolor;
        }
        if( printMap[current_pos.x + 1  ][current_pos.y ] == 1 )
        {
            printMap[current_pos.x + 1  ][current_pos.y ] = obserstatecolor;
        }
    }
}

void Agent_H::spawnApple(int x, int y)
{

    if(m_Room->worldMap[x][y] == 1)
        m_Room->worldMap[x][y] = 3;
    else
    {
        spawnApple(rand()% m_Room->x_size, rand()% m_Room->x_size);
    }
}

void Agent_H::cleanExplorationMap()
{
    for (int i = 0; i < m_Room->x_size; i++)
    {
        for(int j = 0; j < m_Room->y_size; j++)
        {
            explorationMap[i][j] = 0;
        }
    }
}

void Agent_H::checkBlockedSensor(int s0x, int s0y, int s1x, int s1y, int s2x, int s2y, int s3x, int s3y)
{
    sensor3x = s3x;
    sensor3y = s3y;
    sensor2x = s2x;
    sensor2y = s2y;
    sensor1x = s1x;
    sensor1y = s1y;
    sensor0x = s0x;
    sensor0y = s0y;

    if (m_Room->worldMap[sensor3x][sensor3y] == 0)
    {
        current_state[0] = 0;
        current_state[1] = 0;
        current_state[2] = 0;
        current_state[3] = 0;
    }
    else if(m_Room->worldMap[sensor2x][sensor2y] == 0)
    {
        current_state[0] = 0;
        current_state[1] = 0;
        current_state[2] = 0;
        current_state[3] = m_Room->worldMap[sensor3x][sensor3y];
    }
    else if(m_Room->worldMap[sensor1x][sensor1y] == 0)
    {
        current_state[0] = 0;
        current_state[1] = 0;
        current_state[2] = m_Room->worldMap[sensor2x][sensor2y];
        current_state[3] = m_Room->worldMap[sensor3x][sensor3y];
    }
    else
    {
        current_state[0] = m_Room->worldMap[sensor0x][sensor0y];
        current_state[1] = m_Room->worldMap[sensor1x][sensor1y];
        current_state[2] = m_Room->worldMap[sensor2x][sensor2y];
        current_state[3] = m_Room->worldMap[sensor3x][sensor3y];
    }
}



void Agent_H::runAgent(int _episodes, int _totalsteps)
{
    m_Room->initializeTrash(15);
    *rewardVec = std::vector<double>(_totalsteps);
    *Qvalue = std::vector<double>(_totalsteps + 1);
    *Qvaluetotal = std::vector<double>(_episodes + 1);
    *Qincrement = std::vector<double>(_totalsteps + 1);
    *wall_vec = std::vector<int>(_totalsteps + 1);
    std::vector<std::vector<int>> good_action(_episodes + 1, std::vector<int>(2));

    int size_TPM = 2000;
    TransitionMatrix TM(size_TPM, num_act);

    std::stringstream workingfolder1, workingfolder2, workingfolder3, workingfolder4, workingfolder6;
    if(savedata == 1)
    {
    // set up new file directory
    workingfolder1<<"../Visualisation_heading/World/"<<currentDateTime()<<"/";
    workingfolder2<<"../Visualisation_heading/Reward/"<<currentDateTime()<<"/";
    workingfolder3<<"../Visualisation_heading/wall_vec/"<<currentDateTime()<<"/";
    workingfolder4<<"../Visualisation_heading/wall_avoiding/"<<currentDateTime()<<"/";
    workingfolder6<<"../Visualisation_heading/Exploration/Explore_"<<currentDateTime()<<"/";

    create_directory(workingfolder1.str());
    create_directory(workingfolder2.str());
    create_directory(workingfolder3.str());
    create_directory(workingfolder4.str());
    create_directory(workingfolder6.str());
    }


    for(int i = 0; i < _episodes; i++ )
    {
        std::stringstream workingfolder5;
         workingfolder5<<workingfolder1.str()<<i<<"/";
         create_directory(workingfolder5.str());

        // Initialization
        current_pos = { x_start , y_start };
        resetCurrentState();
        steps = 0;
        totalreward = 0;
        reward = 0;
        m_Room->cleanWorldMap();
        m_Room->worldMap = m_Room->setMap;
        m_Room->worldMap[current_pos.x][current_pos.y + 2] = 3;
        printMap = m_Room->worldMap;
        printMap[x_start][y_start + 2] = 3;
        printMap[current_pos.x][current_pos.y] = 5;

        int right_action = 0;
        int it_turns_right = 0;
        int turns_right = 0;

        // Agent runs
        while(steps < _totalsteps)
        {
            performAction(_episodes, i);

            sol_met->updateQtable(this);
            Qincrement->at(steps) = sol_met->getQtableincrement(this);
            Qvalue->at(steps) = sol_met->getQvalue(this);
            TM.increment(old_state, current_state, action);

            if(current_state[3] == 0)
            {
                good_action[i][0] = good_action[i][0] + 1;
                wall_vec->at(steps) = 1;

            if(reward != -10)
            {
                good_action[i][1] = good_action[i][1] + 1;
            }


            }

            if(current_state[4] == 3 | current_state[5] == 3)
            {

                if(action == TURN_RIGHT)
                {
                    turns_right++;
                }
            }

            if(action == TURN_RIGHT)
            {
                it_turns_right++;
            }


            if(BLKB->get("action") == BLKB2->get("action"))
            {
                right_action = right_action + 1;
            }

            if (savedata == 1)
            {
            setSensorInformation();
            save.printAgentinRoom(steps, printMap, workingfolder5.str());
            }


            if(i == _episodes - 1){
                if(savedata == 1){

                    //save.printAgentReward(rewardVec, workingfolder2.str());
                } // save
            } // last episode
        } // end run


        std::cout << "Successful action identification rate: \t" << double( right_action ) / double ( _totalsteps)  << "\t" << "The total reward is: " << totalreward << "\t" << " And it turned right: " <<  it_turns_right  << " times, to act on trash it was: \t" << turns_right  << "\n";

        Qvaluetotal->at(i) = sol_met->sumQvalues();

        if (i == _episodes - 1)
        {
            save.printQincrement(Qincrement);
            int sum_of_elems = 0;
            for (int n : *Qvalue){
                sum_of_elems += std::abs(n);}

            std::cout << "KHEPERA_AGENT_HEADING:: Total reward last episode: " << totalreward << "\n";

            //Qvalue->push_back(sum_of_elems);
            //save.printQvalue(Qvalue);
            save.printQvaluetotal(Qvaluetotal);
        }

//        if (i % 1 == 0)

//        save.printAgentReward(rewardVec, workingfolder2.str(), i);
//        save.printwallencounter(wall_vec,workingfolder3.str(),i);
//        totalRewardVec.push_back(std::pair<int,double> (i, totalreward));
//        save.printAgentExploration(i,workingfolder6.str() ,explorationMap);

        std::fill(wall_vec->begin(), wall_vec->end(), 0);

        cleanExplorationMap();
    }

    std::cout << "This is the QTable size: " << sol_met->getSizeQtable() << "\n";

    //TM.calculateTPM(sol_met->getSizeQtable(), num_act);

    if(savedata == 1)
    {
        save.printTPM_discrete_distribution(TM.transitionMatrix_count, sol_met->getSizeQtable());
        save.printwallAvoiding(good_action, workingfolder4.str());
        save.printAgentRewardperEpisode(totalRewardVec);
        TM.storeKeyandMap();
        save.printTPMunorderedMap(TM.string2intMap1);
    }

}

void Agent_H::resetCurrentState()
{
    current_state[0] = 1;
    current_state[1] = 1;
    current_state[2] = 3;
    current_state[3] = 1;
    current_state[4] = 1;
    current_state[5] = 1;
    current_state[6] = 1;
    current_state[7] = 1;
}




