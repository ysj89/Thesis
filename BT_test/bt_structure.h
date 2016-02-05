#ifndef BT_STRUCTURE_H
#define BT_STRUCTURE_H


namespace BT_Structure
{
    enum Status
    {
        BH_FAILURE,
        BH_SUCCES,
        BH_INVALID,
    };



class Node  // This class represents each node in the behaviour tree.
{
    public:
    Node()
        :m_eStatus(BH_INVALID)
    {}

    virtual ~Node()
    {
    };

    // General
    virtual enum Status update() = 0; // (Virtual) abstract makes sure you have to have a subclass with the function run
    virtual void onInitialise() {}
    virtual void onTerminate(Status) {}
    Status tick();

    Status m_eStatus;
};


};

#endif // BT_STRUCTURE_H
