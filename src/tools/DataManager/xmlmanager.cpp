#include "xmlmanager.h"
#include "tools/Debugger/debug.h"
#include "tools/FunFunctions/fun.h"
#include <sstream>

XMLmanager::XMLmanager(){ }

XMLmanager::~XMLmanager()
{
    inp.close();
    outp.close();
}

void XMLmanager::setFileCloseAtFinish(bool mode)
{
    closeAtFinish=mode;
}

void XMLmanager::setCurrentWorkingFile(std::string fnm)
{
    currentFile=fnm;
    inp.open(fnm);
    if(!inp.is_open()) deb<<"[XMLmanager] Error opening file.\n";
}

void XMLmanager::setEncoding(std::string encode)
{
    //needs checking
    encoding=encode;
}

std::string XMLmanager::getCurrentWorkingFile()
{
    return currentFile;
}

bool XMLmanager::isTagEqual(std::string tag1, std::string tag2, bool ending);
{
    std::string buf;

}

std::string XMLmanager::getOneBlock(std::string tag, bool fromFirstChar, int mode)
{
    if(mode==1) inp.rewind();
    bool endo=false, startOblock=false, startOtag=false;
    std::string buff;
    std::string temp;
    int pass=0;

    while(!endo)
    {
        char c;
        inp.read(c);

        if(startOblock) buff.push_back(c);

        if(c!=char(32) && c!='<' && fromFirstChar) return " ";
        if(c=='<') startOtag=true;

        if(startOtag) temp.push_back(c);

        if(c=='>')
        {
            if(isTagEqual(temp, tag)) startOblock=true;
            temp.clear();
        }


        pass++;
    }
}

bool XMLmanager::isXMLvalid(std::string filename, bool closeFile)
{
    if(Fun::getFileExtension(fileName) != "xml") return false;
    if(inp.is_open()) inp.close();

    inp.open(filename);
    inp.

    return true;
}

std::string XMLmanager::getStringFromLanguageFile(std::string lang, int str_id, std::string fileName, int symKeepMode, bool toCurrentEncoding)
{
    if(fileName=="...") fileName = currentFile;
    if(!isXMLvalid(fileName, false)) return "Error - XML file not valid.";


    std::string tempo;
    getline(inp, tempo);


}


//end;
