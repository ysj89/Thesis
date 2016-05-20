#include "bt_composite.h"

//bt_composite::bt_composite()
//{

//}


namespace BT_Structure
{

enum Status Selector::update(blackboard *BLKB)
{
    for (Node* child : getChildren())
    {  // The generic Selector implementation
        // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.

        if (child->update(BLKB))
            return BH_SUCCES;
    }
    return BH_FAILURE;  // All children failed so the entire run() operation fails.
}

enum Status Sequence::update(blackboard *BLKB)
{
    for (Node* child : getChildren())
    {   // The generic Sequence implementation.
        // If one child fails, then enter operation run() fails.  Success only results if all children succeed.

        if (!child->update(BLKB))
            return BH_FAILURE;
    }
    return BH_SUCCES;  // All children suceeded, so the entire run() operation succeeds.

}


// KIRK - GP: returns number children in composite
size_t CompositeNode::kChildren()
{
    return m_children.size();
}


// KIRK - GP: returns child from composite
Node* CompositeNode::getChild(size_t k_child)
{
    return m_children[k_child];
}

// KIRK - GP:  replaces a child, returns replaced child
Node *CompositeNode::replaceChild(Node *task, size_t k_child, size_t isNew)
{
        // check parallel for concurrency issues, if apparent do not replace child
        if(!this->canFit(task, 0))
        {
            if (isNew)
            {
                if (task->type.compare("composite") == 0)
                    delete (CompositeNode*)task;
                else
                    delete task;
            }
            return NULL;
        }

        Node* old_child = m_children[k_child];
        m_children[k_child] = task;
        return old_child;
}

    // replaces a child, returns replaced child
bool CompositeNode::canFit(Node *task, size_t parallel_found)
{
        // YSJ:: does not have any parallel nodes
        // check parallel for concurrency issues, if apparent do not replace child
        //if(parallel_found || (task->type.compare("action") == 0 && this->function.compare("parallel") == 0))
        //{
            for ( size_t i = 0; i < m_children.size(); i++ )
            {
                if (this->m_children[i]->type.compare("composite") == 0)
                {
                    if (!((CompositeNode*)this->m_children[i])->canFit(task, 1))
                        return false;
                }
                else if (this->m_children[i]->type.compare("action") == 0 && this->m_children[i]->function.compare(task->function) != 0)
                    return false;
            }

        //}

        return true;

}


// delete child from composite
void CompositeNode::deleteChild(size_t k_child)
{
        if (m_children[k_child]->type.compare("composite") == 0)
        {
            if (m_children[k_child] != NULL)
                delete (CompositeNode*)m_children[k_child];
        }
        else
        {
            if (m_children[k_child] != NULL)
                delete m_children[k_child];
        }
        m_children.erase(m_children.begin() + k_child);
}

}
