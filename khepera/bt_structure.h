#ifndef BT_STRUCTURE_H
#define BT_STRUCTURE_H

//#include "khepera_agent.h"
#include "khepera_agent_heading.h"
#include "solution_method.h"
#include "blackboard.h"


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
    Node(std::string Name, std::string Type, std::string Function)
        :m_eStatus(BH_INVALID),
          name(Name),
          type(Type),
          function(Function)
    {}

    virtual ~Node()
    {};

    // General
    virtual enum Status update(blackboard *BLKB) = 0; // (Virtual) abstract makes sure you have to have a subclass with the function run

    enum Status tick(blackboard *BLKB);

    virtual void onInitialise() {}
    virtual void onTerminate(Status) {}

    Status m_eStatus;
    std::string name;       // KIRK
    std::string type;       // KIRK
    std::string function;   // KIRK

};


}

#endif // BT_STRUCTURE_H
