#ifndef BT_COMPOSITE_H
#define BT_COMPOSITE_H

//#include "bt_structure.h"

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

    protected:
        virtual void onInitialise(){m_currentChild = m_children.begin();}
        virtual enum Status update();

    virtual ~Selector()
    {
    }

};

// Sequence behavior
class Sequence : public CompositeNode
{
    childs::iterator m_current;

protected:
    virtual void onInitialise(){m_current = m_children.begin();}

public:
    virtual enum Status update();


protected:
    virtual ~Sequence()
    {
    }


};


}
#endif // BT_COMPOSITE_H
