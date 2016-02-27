/*Coded by H3nt4iB{}y (Gryllotalpa) (C) 2015
--- Various Functions For Fun ---  v1.3

- Type Converters
- Finders
- Other functions:
  - Time string getter
  - More to come!

- 1.3 additions:
- WinFun class for Windows-specific funcs
- Type converter to bytes

* Main Header
*/

#ifndef FUN_H_INCLUDED
#define FUN_H_INCLUDED

#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>

//Standard funcs

class Fun
{
public:
    Fun(){ }
    ~Fun(){ }

    static double stringToDouble(std::string str, int where);
    static double stringToDoubleRem(std::string str, int & where);
    static double stringToDoubleRemA(std::string str, int where, int & remain);
    static int stringToInt(std::string str, int where=0);
    static void reverseDouble(double & num);
    static bool findTextComplex(std::string mainStr, std::string text, int where);
    static bool findText(std::string mainStr, std::string textToSearch, int where);
    static std::string getTimeString(std::string mode = "%x %X");
    static std::string getFileExtension(std::string filename);
    static std::string reverseString(std::string str);
    static std::vector<std::string> stringToWordArray(std::string str);
    static bool isDivided(int64_t num, int64_t by_what);
    static std::string getFilenameFromPath(std::string path);

    static bool isSystemBigEndian();

    template <typename T>
    static std::string toString(T const& a);

    template<typename T>
    static T getTypeFromBytes(uint8_t bytes[], int byteLenght, bool useReinterpretCast, bool bigEndian=true); //call like getTypeFromBytes< int >(args)

    //reverse converter 2 come...
    template<typename T>
    static int getBytesFromType(T value, char* byteBuffer, bool useReinterpretCast, bool bigEndian=true);
};

//Implementation section

template <typename T> std::string Fun::toString(T const& a)
{
    std::stringstream strem;
    strem << std::setprecision( 15 ) << a;
    return strem.str();
}

template<typename T>
T Fun::getTypeFromBytes(uint8_t bytes[], int byteLenght, bool useReinterpretCast, bool bigEndian)
{
    int typeSize = sizeof(T);
    T retval = (T)0;

    uint8_t completeBytes[ typeSize ];

    if(bigEndian)
    {
        for(int i=0; i<typeSize; i++)
        {
            if(i < byteLenght) completeBytes[i] = bytes[i];
            else completeBytes[i] = 0;
        }
    }
    else
    {
        for(int i=typeSize-1; i>=0; i--)
        {
            if(i >= typeSize - byteLenght) completeBytes[i] = bytes[i - typeSize + byteLenght];
            else completeBytes[i] = 0;
        }
    }

    for(int i=0; i<typeSize; i++)
    {
        if(bigEndian) retval |= ( (T)completeBytes[i] << i*8);
        else retval |= ( (T)bytes[i] >> i*8);
    }

    return retval;
}

template<typename T>
int Fun::getBytesFromType(T value, char* byteBuffer, bool useReinterpretCast, bool bigEndian)
{
    int typeSize = sizeof(T);
    char* tempo = new char[ typeSize ];

    //check if value is bitwise operable using typeid(T).name();

    if(useReinterpretCast)  tempo = reinterpret_cast< char* >(value);
    else
    {
        for(int i=0; i<typeSize; i++)  tempo[i] = (char)(value >> i*8);
    }

    for(int i=0; i<typeSize; i++)
    {
        if(bigEndian) byteBuffer[typeSize-1-i] = tempo[i];
        else byteBuffer[i]=tempo[i];
    }

    delete [] tempo;

    return typeSize;
}
//standard end

//WinFuncs (indev)
//for this link against "comdlg32"

class WinFun
{
public:
    WinFun(){ }
    ~WinFun(){ }

    static std::string GetOpenSaveFileWindows(int mode, const char filterLine[]="All Files\0*.*\0\0"); //mode: 1-open, 2-save
};


#endif // FUN_H_INCLUDED
