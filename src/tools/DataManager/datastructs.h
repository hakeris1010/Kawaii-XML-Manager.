/* Robo-1 Standard v1.0 (by H3nt4iBoY) data structures
*/

#ifndef DATASTRUCTS_H_INCLUDED
#define DATASTRUCTS_H_INCLUDED

#include <string>
#include <vector>

#define DATA_TYPE_TAG
#define DATA_TYPE_TEXT

struct DataElement
{
    int type;
    std::string content;
};

struct DataStruct
{
    int id;
    std::string title;
    std::string simpleText;
    std::vector<DataElement> elems;
};

#endif // DATASTRUCTS_H_INCLUDED
