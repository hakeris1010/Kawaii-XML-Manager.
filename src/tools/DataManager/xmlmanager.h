/*XML manager v0.1 by H3nt4iBoY
- Supports H3nt4iBoY's data transfer standard (Robo-1)
- More custom standards to come, including "Gryllotalpa's World" standard
- Now supports only ASCII chars, but Unicodes to come!
*/

#ifndef XMLMANAGER_H_INCLUDED
#define XMLMANAGER_H_INCLUDED

#include <fstream>
#include <string>
#include "datastructs.h"

#define XML_MANAGER_VERSION "v0.1 pre"


class XMLmanager
{
//private:
public: //test
    std::ifstream inp;
    std::ofstream outp;
    bool closeAtFinish=false, closeAtEveryFunctionEnd=false;
    std::string encoding="ASCII";
    std::string currentInputFile, currentOutputFile;

    static void printTagContents(XMLTag tag, bool useDebug=true);
    static void printElementContents(XMLElement elem, bool showInnerElements, bool useDebug=true, int recursiveLevel=0);

    bool isXMLvalid(std::string filename, bool closeFile=false);
    //bool isTagEqual(std::string tag1, std::string tag2, bool ending=false); //not good
    bool isTagSelfClose(std::string tagName);
    bool getTagInfoFromString(std::string str, XMLTag &tag);
    bool getOneElementFromFile_StringInside(XMLElement &elem, bool closeFileAtEnd=false, bool rewindFile=false, bool searchForTag=false, std::string searchTagName="",  bool searchFromFirstTag=true);

//public:
    XMLmanager();
    ~XMLmanager();

    void openXMLInputFile(std::string inputFileName);
    void closeCurrentXMLFile(int mode=0); //0 - all, 1 - input, 2 - output

    void setFileCloseAtFinish(bool mode);
    void setCurrentWorkingInputFile(std::string fnm, bool openFile=false);
    void setEncoding(std::string encode);
    std::string getCurrentWorkingInputFile();
    std::string getStringFromLanguageFile(std::string lang, int str_id, std::string fileName="...", int symKeepMode=0, bool toCurrentEncoding=false);
    int getRobo1DataFromFile(DataStruct &cont, int data_id, std::string fileName="...", int symKeepMode=0, bool toCurrentEncoding=false);
};


#endif // XMLMANAGER_H_INCLUDED
