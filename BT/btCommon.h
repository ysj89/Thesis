#ifndef BTCOMMON_H
#define BTCOMMON_H

#define __BEHAVIOURTREE

//#include <iostream>
//#include <vector>
//#include <deque>
//#include <assert.h>
//#include <stdint.h>
//#include <stdlib.h>

#include "behaviour.h"
#include "composites.h"
#include "conditions.h"

#ifdef KHEPERA
	#include "../khepera/kheperaActions.h"
#else // DELFLY
	#include "../delfly/delflyActions.h"
#endif

#endif // BTCOMMON_H
