/*XML manager v0.1 by H3nt4iBoY
- Supports H3nt4iBoY's data transfer standard (Robo-1)
- More custom standards to come, including Gryllotalpa's World standard
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
private:
    std::ifstream inp;
    std::ofstream outp;
    bool closeAtFinish=false;
    std::string encoding="ASCII";
    std::string currentFile;

    bool isXMLvalid(std::string filename, bool closeFile=false);
    bool isTagEqual(std::string tag1, std::string tag2, bool ending=false);
    std::string getOneBlock(std::string tag, bool fromFirstChar=false, int mode=0);

public:
    XMLmanager();
    ~XMLmanager();

    void setFileCloseAtFinish(bool mode);
    void setCurrentWorkingFile(std::string fnm);
    void setEncoding(std::string encode);
    std::string getCurrentWorkingFile();
    std::string getStringFromLanguageFile(std::string lang, int str_id, std::string fileName="...", int symKeepMode=0, bool toCurrentEncoding=false);
    int getRobo1DataFromFile(DataStruct &cont, int data_id, std::string fileName="...", int symKeepMode=0, bool toCurrentEncoding=false);
};


#endif // XMLMANAGER_H_INCLUDED
