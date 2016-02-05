#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

#include "windygridworld.h"
#include "agent.h"
#include "behavior.h"
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_windygrid.h"
#include "conditions.h"

using std::vector;
using namespace std;


Behavior::Behavior()
{

}

namespace bt1
{

class Node;
class Task;

enum Status
{
    BH_INVALID,
    BH_SUCCES,
    BH_FAILURE,
};


class Node
{
public:
    virtual Task* create() = 0;
    virtual void destroy(Task*) = 0;

    virtual ~Node(){}
};


class Task
{
public:
    Task(Node& node)
        : m_pNode(&node)
    {}

    virtual ~Task(){}

    virtual enum Status update() = 0;

    virtual void onInitialize() {}
    virtual void onTerminate(Status) {}

protected:
    Node* m_pNode;
};

} // END NAMESPACE
