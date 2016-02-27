#include "mainrunner.h"
#include "tools/Debugger/debug.h"
#include "tools/FunFunctions/fun.h"
#include "tools/DataManager/xmlmanager.h"

Debug deb;

int testThings()
{
    XMLmanager man;

    std::string inpFile = "AnimeTracker/res/texts/Langs/LT.xml";

    if(man.isXMLvalid(inpFile, false))
        deb<<"\nisXMLvalid() returned true!\n";
    else
    {
        deb<<"\nisXMLvalid() returned false!\nReturn -1.\n";
        return -1;
    }

    /*deb<<"\n= = = = = = = = = = = = =\nValidity Chex0r3d, now getting an element!\n";
    XMLElement elemz;

    if(man.getOneElementFromFile_StringInside(elemz))
    {
        deb<<"\n---------------\nGot element! Elem. contents: \n";
        man.printElementContents(elemz, false);
    }
    else
        deb<<"\n---------------\nElemeng getting Failed!\n";*/

    return 0;
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
