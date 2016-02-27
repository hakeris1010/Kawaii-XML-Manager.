/* Robo-1 Standard v1.0 (by H3nt4iBoY) data structures
*/

#ifndef DATASTRUCTS_H_INCLUDED
#define DATASTRUCTS_H_INCLUDED

#include <string>
#include <vector>

#define DATA_TYPE_TAG
#define DATA_TYPE_TEXT

//Robo-1
struct DataElement
{
    int type;
    std::string content;
};

class DataStruct
{
public:
    DataStruct(){ }
    ~DataStruct(){ clearThis(); }

    int id;
    std::string title;
    std::string simpleText;
    std::vector<DataElement> elems;

    void clearThis()
    {
        id=0;
        title.clear();
        simpleText.clear();
        elems.clear();
    }
};

//XML-Type

#define XML_TAGTYPE_INITIALIZE "init" // the <?...?> tag
#define XML_TAGTYPE_BEGIN      "beg" // <...> tag
#define XML_TAGTYPE_END        "end" // </...> tag
#define XML_TAGTYPE_SELFCLOSE  "close" // <... /> tag, or specific, predefined (like <br>)

struct XMLAttrib
{
    std::string name;
    std::string value;

    void clearThis()
    {
        name.clear();
        value.clear();
    }
};

class XMLTag
{
public:
    XMLTag(){ }
    ~XMLTag(){ clearThis(); }

    std::string tagName;
    std::string tagType; //can be int
    std::vector<XMLAttrib> attribs;

    void clearThis()
    {
        tagName.clear();
        tagType.clear();
        attribs.clear();
    }
};

class XMLElement
{
public:
    XMLElement(){ }
    ~XMLElement(){ clearThis(); }

    XMLTag mainTag;
    //std::string tagString;         //in tagObject
    //std::vector<XMLAttrib> attribs;
    std::string text;
    std::vector<XMLElement> innerElements;

    void clearThis()
    {
        mainTag.clearThis();
        text.clear();
        //tagString.clear();
        //attribs.clear();
        innerElements.clear();
    }
};

#endif // DATASTRUCTS_H_INCLUDED
