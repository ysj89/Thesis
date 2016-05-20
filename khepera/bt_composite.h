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

typedef std::vector<Node*> nodes;


class CompositeNode : public Node  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
{

public:
    const std::vector<Node*>& getChildren() const {return m_children;}
    void addChild (Node* child) {m_children.emplace_back(child);}
    void clearChildren();


    size_t kChildren();                                                 // KIRK: For GP
    Node* getChild(size_t k_child);                                     // KIRK: For GP
    Node* replaceChild(Node* task, size_t k_child, size_t isNew = 0);   // KIRK: For GP
    bool canFit(Node* task, size_t parallel_found);                     // KIRK: FOR GP
    void deleteChild(size_t k_child);                                   // KIRK: FOR GP

protected:
    nodes m_children;

    CompositeNode(std::string Name, std::string Type, std::string Function) :
        Node( Name, Type, Function )
{
}

};




// Selector behavior
class Selector : public CompositeNode
{
protected:
    nodes::iterator m_currentChild;
    int chooseAction(blackboard *BLKB){return 0;};

public:
    Selector():
        CompositeNode("selector", "composite", "selector")
    {}
    virtual ~Selector()
    {}

    virtual void onInitialise(){m_currentChild = m_children.begin();}
    virtual enum Status update(blackboard *BLKB);

};

// Sequence behavior
class Sequence : public CompositeNode
{
protected:
    nodes::iterator m_current;
    int chooseAction(blackboard *BLKB){return 0;};

public:
    Sequence():
        CompositeNode("sequence", "composite", "sequence")
    {}
    virtual ~Sequence()
    {}

    virtual void onInitialise(){m_current = m_children.begin();}
    virtual enum Status update(blackboard *BLKB);

};


}

#endif // BT_COMPOSITE_H
