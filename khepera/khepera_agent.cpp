#include "khepera_agent.h"

void Agent::performAction()
{
    old_pos = current_pos;

    action = sol_met->getAction(current_pos);

        // Probability of succesfull execution of action
            if ( (rand() % 100 + 1) / 100.0  < succes_probability)
            {
                action = action;
            }
            else
            {
                action = static_cast<Action> ( rand()%4 );
            }

        // Perform action
            switch(action)
            {
            case UP:
                current_pos.y -= 1;
                break;
            case RIGHT:
                current_pos.x += 1;
                break;
            case DOWN:
                current_pos.y += 1;
                break;
            case LEFT:
                current_pos.x -= 1;
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

        // Check walls
            if(m_Room->worldMap[current_pos.x][current_pos.y] = 1)
            {
                current_pos = old_pos;
            }
            else
            {};



time = time + 1;

}


