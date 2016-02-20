#include "mainrunner.h"
#include "tools/Debugger/debug.h"
#include "tools/FunFunctions/fun.h"

Debug deb;

void testThings()
{

}

int main()
{
    deb.setMode(DEBUG_TO_SCREEN);
    deb<<"[int main()] Starting!!!\n";

    testThings();

    int arg=0;
    int retval = startTheShit(arg);

    if(arg != retval) deb<<"\nError occured!\n";

    return retval;
}
