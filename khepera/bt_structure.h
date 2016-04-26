#ifndef BT_STRUCTURE_H
#define BT_STRUCTURE_H

//#include "khepera_agent.h"
#include "khepera_agent_heading.h"
#include "solution_method.h"


namespace BT_Structure
{
    enum Status
    {
        BH_FAILURE,
        BH_SUCCES,
        BH_INVALID,
        BH_RUNNING,
    };

    class Node : public Solution_method  // This class represents each node in the behaviour tree.
    {
        public:
        Node()
            :m_eStatus(BH_INVALID)
        {}

        virtual ~Node()
        {
        };

        // General
        virtual enum Status update(blackboard *BLKB) = 0; // (Virtual) abstract makes sure you have to have a subclass with the function run

        enum Status tick(blackboard *BLKB);

        virtual void onInitialise() {}
        virtual void onTerminate(Status) {}
        Status tick();

        Status m_eStatus;
    };


}

#endif // BT_STRUCTURE_H
