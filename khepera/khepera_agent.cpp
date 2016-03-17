#include "khepera_agent.h"

void Agent::performAction()
{
    old_pos = current_pos;
    old_state = current_state;
    old_action = current_action;


    current_action = sol_met->getAction(current_state);

        // Probability of succesfull execution of action
            if ( (rand() % 100 + 1) / 100.0  > succes_probability)
            {
                current_action = static_cast<Action> ( rand()%4 );
            }



        // Perform action
            switch(current_action)
            {
            case UP:
                current_pos.x -= 1;
//                reward = -1;
                break;
            case RIGHT:
                current_pos.y += 1;
//                reward = -1;
                break;
            case DOWN:
                current_pos.x += 1;
//                reward = -1;
                break;
            case LEFT:
                current_pos.y -= 1;
//                reward = -1;
                break;


            default:
                std::cout << "\n Class:Agent :: Perform Action not implemented \n" ;
            }


        // Out of bound check
            while(current_pos.x < 0 )
            {
                current_pos.x = old_pos.x;
            }
            while(current_pos.y < 0 )
            {
                current_pos.y = old_pos.y;
            }
            while(current_pos.x > m_Room->x_size - 1)
            {
                current_pos.x = old_pos.x;
            }
            while(current_pos.y > m_Room->y_size -1)
            {
                current_pos.y = old_pos.y;
            }

        // Wall check
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 1) // NOTE: Agent hit a wall, returns to old position
            {
                current_pos = old_pos;
                reward = -10;
            }
            if(m_Room->worldMap[current_pos.x][current_pos.y] == 2) // NOTE: Agent found trash, automatically cleans it and picks it up
            {
                reward = 20;
                m_Room->worldMap[current_pos.x][current_pos.y] = 0;
                m_Room->setTrash();
            }


                                            // Observable states
                                            //       y1  y2  y3
                                            //  x0
                                            //  x1    7   0   1
                                            //  x2    6 Agent 2
                                            //  x3    5   4   3
                                            //  x4    8 = batterylife NOTE: not implemeted yet

        // Read sensors [empty, wall, trash]
            current_state[0] = m_Room->worldMap[current_pos.x - 1][current_pos.y    ];
            current_state[1] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
            current_state[2] = m_Room->worldMap[current_pos.x    ][current_pos.y + 1];
            current_state[3] = m_Room->worldMap[current_pos.x + 1][current_pos.y + 1];
            current_state[4] = m_Room->worldMap[current_pos.x + 1][current_pos.y    ];
            current_state[5] = m_Room->worldMap[current_pos.x + 1][current_pos.y - 1];
            current_state[6] = m_Room->worldMap[current_pos.x    ][current_pos.y - 1];
            current_state[7] = m_Room->worldMap[current_pos.x - 1][current_pos.y - 1];


    steps = steps + 1;
    totalreward = totalreward + reward;


}

void Agent::runAgent(int _episodes, int _totalsteps)
{
    for(int i = 0; i < _episodes; i++ )
    {
        current_pos = { 2 , 2 };
        m_Room->initializeTrash();
        steps = 0;
        totalreward = 0;

        while(steps < _totalsteps)
        {
            performAction();
            sol_met->update(this);

        }

        std::cout << "This was episode: " << i << "\t with a total reward of: " << totalreward << "\n";
    }
}







