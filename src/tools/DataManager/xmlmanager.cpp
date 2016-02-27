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

void XMLmanager::setCurrentWorkingInputFile(std::string fnm, bool openFile)
{
    currentInputFile=fnm;
    if(openFile)
    {
        inp.open(fnm);
        if(!inp.is_open()) deb<<"[XMLmanager] Error opening file.\n";
    }
}

void XMLmanager::setEncoding(std::string encode)
{
    //needs checking
    encoding=encode;
}

std::string XMLmanager::getCurrentWorkingInputFile()
{
    return currentInputFile;
}

bool XMLmanager::isTagSelfClose(std::string tagName)
{
    /*switch(tagName)
    {
    case "br":
    case "enter_text"
        return true;
    }*/

    if(tagName=="br" || tagName=="enter_text") return true;

    return false;
}

bool XMLmanager::getTagInfoFromString(std::string str, XMLTag &tag)
{
    bool dbg=true;

    if(dbg) deb<<"\n-*-*-*-*-*-*-*-*-*-*-\ngetTagInfoFromString():\n\nstr= "<<str<<"\nSetting vars...\n";

    bool isEmpty=true, afterSpace=false, onParam=false, onValue=false, isGood=true, areLetters=false, afterLygu=false, paramEnded=false, endOfTag=false;
    std::string tagType, name, temp;
    char lastChar='<';
    XMLAttrib tempatr;

    if(dbg) deb<<"Luupu Sutarto! (^_^)\n\n";

    for(int i= (str[0]=='<' ? 1 : 0 ); i<str.size(); i++)
    {
        if(str[i] > char(32) && str[i] < char(127))
        {
            if(isEmpty)
            {
                if(dbg) deb<<"isEmpty: str["<<i<<"]= "<<str[i]<<"\n";

                if(str[i] == '\?' /*|| (str.size() > i+3 ? (str[i]=='\?' && str[i+1]=='x' && str[i+2]=='m' && str[i+3]=='l') : false )*/ )
                    tagType = XML_TAGTYPE_INITIALIZE;
                else if(str[i] == '/')
                    tagType = XML_TAGTYPE_END;
                else
                {
                    tagType = XML_TAGTYPE_BEGIN;
                    i--;
                }

                if(dbg) deb<<"tagType= "<<tagType<<"\nisEmpty= false.\n";

                isEmpty = false;
            }

            else
            {
                if(str[i]=='>' || i>=str.size()-1) //end reached;
                {
                    if(dbg) deb<<"End of Tag reached! Soon will return...\n\n";
                    endOfTag = true;
                }

                /*if(paramEnded && !endOfTag)
                {
                    if(dbg) deb<<"paramEnded not on place. isGood=false\n";
                    isGood=false;
                    break;
                }*/

                if(!onParam && !onValue) //onName
                {
                    if((afterSpace && name.size()>0) || endOfTag)
                    {
                        if(dbg) deb<<"[0,0]: onName: ((afterSpace && name.size()>0) || endOfTag):\n  NameEnded. onParam=true,\ntag.tagName= name= "<<name<<"\n";
                        onParam=true;
                        tag.tagName = name;
                        name.clear();
                    }
                    else
                        name.push_back(str[i]);
                }

                if(onParam && !onValue && !endOfTag) //on ParamName
                {
                    if(str[i]=='=')
                    {
                        if(dbg) deb<<"[1,0]: on ParamName: afterLygu= true (on \'=\')\n";
                        afterLygu=true;
                    }
                    else
                    {
                        if(afterLygu && str[i]=='\"' && temp.size()>0) //end o' ParamName
                        {
                            if(dbg) deb<<"[1,0]: on ParamName:\nend of ParamName (afterLygu, on \", temp>0):\nonValue= true, atr.name= temp= "<<temp<<"\n";
                            onValue=true;
                            tempatr.clearThis(); //clearing the temp attrib struct
                            tempatr.name = temp; //asign new name to tempatr
                            temp.clear();
                        }
                        else if(afterLygu && (str[i]!='\"' || temp.size()==0))
                        {
                            if(dbg) deb<<"[1,0]: on ParamName:\nbad shit happened. (afterLygu and not \") isGood=false\n(str[i]= "<<str[i]<<")\n";
                            isGood=false;
                            break;
                        }
                    }

                    if(!afterLygu)
                        temp.push_back(str[i]);
                }

                else if(onParam && onValue) //onValue (after lygu)
                {
                    afterLygu = false;

                    if(str[i]=='\"' && temp.size()>0)
                    {
                        if(dbg) deb<<"[1,1]: onValue:\nonValue=false, paramEnded=true,\ntempatr.value=temp= "<<temp<<"\nAssigning attrib to tag...\n";
                        onValue=false;
                        paramEnded=true;

                        tempatr.value = temp;
                        tag.attribs.push_back(tempatr);

                        temp.clear();
                    }
                    else
                        temp.push_back(str[i]);
                }
            }

            afterSpace = false;
            areLetters = true;

            if(i>0) lastChar = str[i];
        }
        else if(str[i] == char(32) || str[i] == '\n' || str[i] == '\t')
        {
            if(!isEmpty) afterSpace=true;

            if(paramEnded)
            {
                if(dbg) deb<<"onSpace: paramEnded=false\n";
                paramEnded=false;
            }
            if(onParam && onValue)
                temp.push_back(str[i]);
        }
        else
        {
            if(dbg) deb<<"bad char. (str[i]= "<<str[i]<<"). isGood=false, break.\n";
            isGood=false;
            break;
        }
    }

    if(!areLetters || tag.tagName.empty())
    {
        if(dbg) deb<<"no Letters || no tagName\nisGood=false\n";
        isGood=false;
    }

    if(!isGood)
    {
        if(dbg) deb<<"-*-*-*-*-*-*-*-*-*-*-*-\n";
        return false;
    }

    if(isTagSelfClose(tag.tagName)) tagType = XML_TAGTYPE_SELFCLOSE;

    tag.tagType = tagType;
    if(dbg) deb<<"endTagType=tagType\nReturn true!\n-*-*-*-*-*-*-*-*-*-*-*-\n";

    return true;
}

bool XMLmanager::getOneElementFromFile_StringInside(XMLElement &elem, bool closeFileAtEnd, bool rewindFile, bool searchForTag, std::string searchTagName,  bool searchFromFirstTag)
{
    bool dbg=true;

    if(dbg) deb<<"\n--------------------\ngetOneElement_String():\n\nsearchTagName: "<<searchTagName<<", searchFromFirst: "<<searchFromFirstTag<<"\n";

    if(rewindFile)
    {
        deb<<"Rewinding...\n";
        inp.seekg(0, inp.beg); //reset
    }

    if(dbg) deb<<"Setting vars...\n";

    enum EndCond { Default_OK, Default_BAD,
                   Search_Found, Search_NOTFound };

    bool endo=false, startOblock=false, startOtag=false;
    std::string buff, temp;
    int counter=0;
    EndCond endCondition = Default_BAD;

    if(dbg) deb<<"Loop start!\n";

    while(!endo && !inp.eof())
    {
        char c[1] = { char(32) };

        inp.read(c, 1); //reading one char

        if(!startOblock && !startOtag) //total beginning
        {
            if(c[0]!='<') continue;
            else
            {
                if(dbg) deb<<"[0,0]: Found tag start symbol! startOtag=true\n";
                startOtag = true;
            }
        }
        if(!startOblock && startOtag)
        {
            temp.push_back(c[0]);

            if(c[0]=='>')
            {
                if(dbg) deb<<"[0,1]: Found tagEnd symbol! Temp: "<<temp<<"\nGetting info from tag...\n";

                XMLTag tagg;
                if(!getTagInfoFromString(temp, tagg)) //getting the tag!
                {
                    if(dbg) deb<<"Tag is not valid!\nendCon = BAD, Breaking!\n";
                    endCondition = Default_BAD;
                    break;
                }

                if(dbg) printTagContents(tagg);

                if(searchForTag)
                {
                    if(dbg) deb<<"searchForTag=true!\n";
                    if((tagg.tagName != searchTagName || tagg.tagType == XML_TAGTYPE_END) && searchFromFirstTag)
                    {
                        if(dbg) deb<<"endCond NOT FOUND!!! Break.\n";
                        endCondition = Search_NOTFound;
                        break;
                    }
                }

                if(tagg.tagType != XML_TAGTYPE_END)
                {
                    if(dbg) deb<<"Tag type is good! assigning to elem.\n";
                    elem.mainTag = tagg;

                    if(tagg.tagType == XML_TAGTYPE_BEGIN)
                    {
                        startOblock = true;
                        if(dbg) deb<<"tagType=BEGIN, startOblock= true\n";
                    }

                    else if(tagg.tagType == XML_TAGTYPE_SELFCLOSE || tagg.tagType == XML_TAGTYPE_INITIALIZE)
                    {
                        if(dbg) deb<<"Tag is SelfClose or Initializing. EndCond=Default_OK, break!\n";
                        endCondition = Default_OK;
                        break;
                    }
                }

                if(dbg) deb<<"startOtag= false\n";
                startOtag = false;
                temp.clear();

                continue;
            }
        }
        if(startOblock && !startOtag)
        {
            if(c[0]=='<')
            {
                if(dbg) deb<<"[1,0]: innerBlock tagStart. startOtag=true\nCurrentBuf= temp: "<<temp<<"\n";
                startOtag=true;
                temp.clear();
            }
            else
                buff.push_back(c[0]);
        }
        if(startOblock && startOtag)
        {
            temp.push_back(c[0]);

            if(c[0]=='>')
            {
                if(dbg) deb<<"[1,1]: innerBlock TagEnd. Temp: "<<temp<<"\nGetting TagInfo...\n";

                XMLTag tgg;
                if(!getTagInfoFromString(temp, tgg)) //getting the tag!
                {
                    if(dbg) deb<<"Tag is not valid!\nendCon = BAD, Breaking!\n";
                    endCondition = Default_BAD;
                    break;
                }

                if(dbg) printTagContents(tgg);

                if(tgg.tagType == XML_TAGTYPE_END && tgg.tagName == elem.mainTag.tagName)
                {
                    if(dbg) deb<<"MainTag tagEND found! setting last info into elem...\nstartOblock= false\nendCond= OK. break!\n";

                    elem.text = buff;
                    startOblock=false;

                    if(searchForTag) endCondition = Search_Found;

                    endCondition = Default_OK;
                    break;
                }

                if(dbg) deb<<"Tag's not mainTag End. startOtag= false\n";

                buff += temp;
                startOtag = false;
                temp.clear();

                if(dbg) deb<<"current buff: "<<buff<<"\n";
            }
        }

        counter++;
    }

    if(inp.eof()) endCondition = Default_BAD;

    if(closeFileAtEnd || closeAtEveryFunctionEnd) inp.close();

    deb<<"\nLoop end. Counter= "<<counter<<"\n----------------------\n";

    if(endCondition == Default_OK || endCondition == Search_Found) return true;
    return false;
}

void XMLmanager::printElementContents(XMLElement elem, bool showInnerElements, bool useDebug, int recursiveLevel)
{
    deb<<"\nprintElementContents( "<<recursiveLevel<<" ):\n\nelem.mainTag.tagName = "<<elem.mainTag.tagName<<"\n";
    deb<<"elem.mainTag.tagType = "<<elem.mainTag.tagType<<"\n\n";

    for(int i=0; i<elem.mainTag.attribs.size(); i++)
        deb<<"elem.mainTag.attribs["<<i<<"]: name= "<<elem.mainTag.attribs[i].name<<", value= "<<elem.mainTag.attribs[i].value<<"\n";

    deb<<"\nelem.text = "<<elem.text<<"\n";

    if(showInnerElements)
    {
        deb<<"\nInnerElements: \n";
        for(int i=0; i<elem.innerElements.size(); i++)
            printElementContents(elem.innerElements[i], showInnerElements, useDebug, recursiveLevel+1);
    }
    deb<<"\n";
}

void XMLmanager::printTagContents(XMLTag tag, bool useDebug)
{
    deb<<"\nprintTagContents():\n\ntag.tagName = "<<tag.tagName<<"\n";
    deb<<"tag.tagType = "<<tag.tagType<<"\n\n";

    for(int i=0; i<tag.attribs.size(); i++)
        deb<<"tag.attribs["<<i<<"]: name= "<<tag.attribs[i].name<<", value= "<<tag.attribs[i].value<<"\n";

    deb<<"\n";
}

bool XMLmanager::isXMLvalid(std::string filename, bool closeFile)
{
    deb<<"\nChecking XML File Validity...\n";

    if(Fun::getFileExtension(filename) != "xml") return false;
    if(inp.is_open()) inp.close();

    inp.open(filename);

    char cr[1] = { char(32) };
    std::string conts;
    bool isFileBad=false;

    XMLElement test;

    if(!getOneElementFromFile_StringInside(test, false, false, true, "xml", true))
    {
        deb<<"Init Tag Not Found!\n";
        isFileBad=true;
    }

    printElementContents(test, false);
    deb<<"\n";

    if(!isFileBad)
    {
        if(test.mainTag.tagType == XML_TAGTYPE_INITIALIZE && test.mainTag.attribs.size()>0)
        {
            deb<<"XML File Seems Valid! version= "<<test.mainTag.attribs[0].value<<"\n";
        }
        else
        {
            deb<<"Weird init tag.\n";
        }
    }

    if(closeFile) inp.close();

    if(isFileBad) return false;
    return true;
}

std::string XMLmanager::getStringFromLanguageFile(std::string lang, int str_id, std::string fileName, int symKeepMode, bool toCurrentEncoding)
{
    deb<<"\n------------------------\ngetStringFromLangFile()\n\n";
    if(fileName=="...") fileName = currentInputFile;
    if(!isXMLvalid(fileName, false)) return "Error - XML file not valid.";


}

void XMLmanager::openXMLInputFile(std::string inputFileName)
{
    currentInputFile = inputFileName;
    inp.open(currentInputFile);
}

void XMLmanager::closeCurrentXMLFile(int mode) //0 - all, 1 - input, 2 - output
{
    if(mode==1 || mode==0)
    {
        if(inp.is_open()) inp.close();
        currentInputFile.clear();
    }
    if(mode==2 || mode==0)
    {
        if(outp.is_open()) outp.close();
        currentOutputFile.clear();
    }
}


//end;
