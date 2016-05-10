#include <sstream>

#include "khepera_agent_heading.h"
//#include "khepera_agent.h"
#include "transitionmatrix.h"



int Agent_H::getAction_f()
{

    int action;
    action = sol_met->chooseAction(BLKB); // choose action and put on blackboard
    action = static_cast<Action_heading> (BLKB->get("action") ); // read action from blackboard
    return action;

    // When running behavior tree
    //sol_met->getAction(BB)

}

void Agent_H::performAction()
{
    old_pos = current_pos;
    old_state = current_state;
    reward = 0;

    action = static_cast<Action_heading> ( getAction_f() ) ;



    // Probability of succesfull execution of action
    //            if ( (rand() % 100 + 1) / 100.0  > 1-succes_probability/steps)
    //            {
    //                action = static_cast<Action_heading> ( rand()%num_act );
    //            }

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
        reward = 100;
        m_Room->worldMap[current_pos.x][current_pos.y] = 1;
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
        current_state[8] = NORTH;

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

        current_state[8] = EAST;
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
        current_state[8] = SOUTH;
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

        current_state[8] = WEST;
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
    BLKB->set("sensor8", current_state[8] ); // sensor8 == heading



}




void Agent_H::setSensorInformation()
{
    double obserstatecolor = 4.2;
    printMap = m_Room->worldMap;
    printMap[current_pos.x][current_pos.y] = 5;

    if(heading == NORTH)
    {
        printMap[current_pos.x - 1][current_pos.y] = obserstatecolor;
        if((current_pos.x - 4 ) > 0)
        {
            printMap[current_pos.x - 4][current_pos.y] = obserstatecolor;
            printMap[current_pos.x - 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x - 3 ) > 0)
        {
            printMap[current_pos.x - 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x - 2 ) > 0)
        {
            printMap[current_pos.x - 2][current_pos.y] = obserstatecolor;
        }

    }
    if(heading == EAST)
    {
        printMap[current_pos.x - 0][current_pos.y + 1] = obserstatecolor;
        if((current_pos.y + 4 ) < m_Room->y_size)
        {
            printMap[current_pos.x - 0][current_pos.y + 4] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y + 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
        }
        else if((current_pos.y + 3 ) < m_Room->y_size)
        {
            printMap[current_pos.x - 0][current_pos.y + 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
        }
        else if((current_pos.y + 3 ) < m_Room->y_size)
        {
            printMap[current_pos.x - 0][current_pos.y + 2] = obserstatecolor;
        }

    }
    if(heading == SOUTH)
    {
        printMap[current_pos.x + 1][current_pos.y] = obserstatecolor;

        if((current_pos.x + 4 ) < m_Room->x_size)
        {
            printMap[current_pos.x + 4][current_pos.y] = obserstatecolor;
            printMap[current_pos.x + 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x + 3 ) < m_Room->x_size)
        {
            printMap[current_pos.x + 3][current_pos.y] = obserstatecolor;
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
        }
        else if((current_pos.x + 2 ) < m_Room->x_size)
        {
            printMap[current_pos.x + 2][current_pos.y] = obserstatecolor;
        }


    }
    if(heading == WEST) // 3
    {
        printMap[current_pos.x - 0][current_pos.y - 1] = obserstatecolor;

        if((current_pos.y - 4 ) > 0)
        {
            printMap[current_pos.x - 0][current_pos.y - 4] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y - 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
        }
        else if((current_pos.y - 3 ) > 0)
        {
            printMap[current_pos.x - 0][current_pos.y - 3] = obserstatecolor;
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
        }
        else if((current_pos.y - 3 ) > 0)
        {
            printMap[current_pos.x - 0][current_pos.y - 2] = obserstatecolor;
        }

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

    int size_TPM = 500;
    TransitionMatrix TM(size_TPM, num_act);

    for(int i = 0; i < _episodes; i++ )
    {
        current_pos = { x_start , y_start };
        steps = 0;
        totalreward = 0;
        reward = 0;
        m_Room->cleanWorldMap();
        m_Room->worldMap = m_Room->setMap;
        m_Room->worldMap[current_pos.x][current_pos.y + 2] = 3;
        printMap = m_Room->worldMap;
        printMap[x_start][y_start + 2] = 3;
        printMap[current_pos.x][current_pos.y] = 5;

        while(steps < _totalsteps)
        {
            performAction();
            sol_met->updateQtable(this);

            Qincrement->at(steps) = sol_met->getQtableincrement(this);
            Qvalue->at(steps) = sol_met->getQvalue(this);

            TM.increment(old_state, current_state, action);

            if(i == _episodes - 1)
            {
                if(savedata == 1)
                {
                    setSensorInformation();
                    save.printAgentinRoom(steps, printMap);
                    save.printAgentReward(rewardVec);

                }
            }

        }


        Qvaluetotal->at(i) = sol_met->sumQvalues();

        if (i == _episodes - 1)
        {
            save.printQincrement(Qincrement);

            int sum_of_elems = 0;
            for (int n : *Qvalue)
            {
                sum_of_elems += std::abs(n);
            }

            std::cout << "AGENT:: The summed Qvalue is: " << sum_of_elems << "\n";

            Qvalue->push_back(sum_of_elems);
            save.printQvalue(Qvalue);
            save.printQvaluetotal(Qvaluetotal);
        }



        if (i % 100 == 0)
        {
            totalRewardVec.push_back(std::pair<int,double> (i, totalreward));
            save.printAgentExploration(i,explorationMap);
        }

        cleanExplorationMap();
    }

    int size_Qtable =  sol_met->getSizeQtable();
    std::cout << "This is the QTable size: " << size_Qtable << "\n";

    TM.calculateTPM(size_Qtable, num_act);

    if(savedata == 1)
    {
        save.printTPM3D(TM.TPM, size_Qtable);
        save.printTPM_discrete_distribution(TM.transitionMatrix_count, size_Qtable);
        save.printAgentRewardperEpisode(totalRewardVec);
        TM.storeKeyandMap();
        save.printTPMunorderedMap(TM.string2intMap1);
    }


    if(_episodes == 1)
    {
        std::cout << "AGENT:: The total reward is: " << totalreward << " \n";
    }
    std::cout << std::endl;


}




