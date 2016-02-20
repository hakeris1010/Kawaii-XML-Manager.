/*Coded by H3nt4iB{}y (Gryllotalpa) (C) 2015
--- Various Functions For Fun ---  v1.2

- Type Converters
- Finders
- Other functions:
  - Time string getter
  - More to come!

* Main Header
*/

#ifndef FUN_H_INCLUDED
#define FUN_H_INCLUDED

#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>


class Fun
{
public:
    Fun(){ }
    ~Fun(){ }

    template <typename T>
    static std::string toString(T const& a);

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
};

template <typename T> std::string Fun::toString(T const& a)
{
    std::stringstream strem;
    strem << std::setprecision( 15 ) << a;
    return strem.str();
}

#endif // FUN_H_INCLUDED
