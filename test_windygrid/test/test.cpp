#include "test.h"

#include "bt_windygrid.h"
#include "bt_structure.h"
#include "bt_composite.h"
#include "bt_conditions.h"
#include "bt_action.h"

using namespace BT_Structure;

void run_test(Agent *TEST_AGENT)
{

    BT_Structure::Less_than Minderdan(7, &TEST_AGENT->pos.x);
    BT_Structure::Equal_to Gelijkaan(7, &TEST_AGENT->pos.x);

    Minderdan.update(TEST_AGENT);
    Gelijkaan.update(TEST_AGENT);

    TEST_AGENT->pos.x +=4;

    Minderdan.update(TEST_AGENT);
    Gelijkaan.update(TEST_AGENT);

    TEST_AGENT->pos.x +=5;

    Minderdan.update(TEST_AGENT);
    Gelijkaan.update(TEST_AGENT);


    TEST_AGENT->pos.x = 4;
    TEST_AGENT->chooseAction();
    BT_Structure::Action_right Rechts(1);
    Rechts.update(TEST_AGENT);
    TEST_AGENT->action = LEFT;
    cout << "The action is now: " << TEST_AGENT->action << endl;
    Rechts.update(TEST_AGENT);

    TEST_AGENT->action = DOWN;
    cout << "The action is now: " << TEST_AGENT->action << endl;
    BT_Structure::Action_left Links(1);
    Links.update(TEST_AGENT);

    TEST_AGENT->action = LEFT;
    cout << "The action is now: " << TEST_AGENT->action << endl;
    BT_Structure::Action_up Omhoog(1);
    Omhoog.update(TEST_AGENT);

    TEST_AGENT->action = RIGHT;
    cout << "The action is now: " << TEST_AGENT->action << endl;
    BT_Structure::Action_down Omlaag(1);
    Omlaag.update(TEST_AGENT);

}
