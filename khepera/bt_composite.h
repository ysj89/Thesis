#ifndef BT_COMPOSITE_H
#define BT_COMPOSITE_H


//class bt_composite
//{
//public:
//    bt_composite();
//};
#include "list"

#include "bt_structure.h"

namespace BT_Structure {


class CompositeNode : public Node  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
{
protected:
    typedef std::list<Node*> childs;
    childs m_children;

public:
    const std::list<Node*>& getChildren() const {return m_children;}
    void addChild (Node* child) {m_children.emplace_back(child);}
    void clearChildren();

};


// Selector behavior
class Selector : public CompositeNode
{
    childs::iterator m_currentChild;

    int chooseAction(blackboard *BLKB){return 0;} ;


public:
    virtual void onInitialise(){m_currentChild = m_children.begin();}
    virtual enum Status update(blackboard *BLKB);

    virtual ~Selector()
    {
    }

};

// Sequence behavior
class Sequence : public CompositeNode
{
    childs::iterator m_current;

    int chooseAction(blackboard *BLKB){return 0;} ;

public:
    virtual void onInitialise(){m_current = m_children.begin();}
    virtual enum Status update(blackboard *BLKB);

    virtual ~Sequence()
    {
    }


};


}

#endif // BT_COMPOSITE_H