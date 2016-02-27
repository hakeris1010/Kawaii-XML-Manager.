/*Coded by H3nt4iB{}y (Gryllotalpa) (C) 2015
--- Various Functions For Fun ---  v1.2

- CPP 1
*/

#include "fun.h"
#include <ctime>

//Standard shit.

void Fun::reverseDouble(double & num)
{
    std::string numstr = toString((int)num);

    double res=0, cnt=1, frac;
    frac= num - (int)num;

    for(int i = 0; i < numstr.size(); i++)
    {
        res= res + ((double)(numstr[i] - 48)) * cnt;
        cnt*=10;
    }

    num = res + frac;
}

double Fun::stringToDouble(std::string str, int where)
{
    int wot=where;
    return stringToDoubleRem(str,wot);
}

double Fun::stringToDoubleRemA(std::string str, int where, int & remain)
{
    remain=where;
    return stringToDoubleRem(str,remain);
}

double Fun::stringToDoubleRem(std::string str, int & where)
{
    if(where > str.size()-1) return 0;

    double res=0, num=1, numfrac=10;
    bool frac=false, quit=false, numfound=false;
    int digs=0;

    for(int i=where; i<str.size(); i++)
    {
        if(str[i]>=48 && str[i]<58)
        {
            numfound=true;
            digs++;
        }
        else
        {
            if(numfound) break;
        }
    }

    num=pow(10, digs-1);

    numfound=false;

    int i;

    for(i=where; i<str.size(); i++)
    {
        if(str[i]>=48 && str[i]<58)
        {
            numfound=true;

            if(!frac)
            {
                res = res + ((double)(str[i]-48)) * num;
                num /= 10;
            }
            else
            {
                res = res + ((double)(str[i]-48)) / numfrac;
                numfrac *= 10;
            }
        }

        else if(str[i]==44 || str[i]==46)
        {
            if(!frac)
            {
                frac=true;
            }
            else
            {
                if(numfound) quit=true;
            }
        }

        else
        {
            if(numfound) quit=true;
        }

        if(quit)
        {
            break; //Stop the loop.
        }
    }

    where=i;

    return res;
}

bool Fun::findTextComplex(std::string mainStr, std::string text, int where)
{
    if(where >= mainStr.size()) return false;
    if(mainStr.size() < text.size()) return false;

    for(int i = 0; i<text.size(); i++)
    {
        if(mainStr[where] == text[i])
        {
            bool cool = true;

            for(int j = where-i; j<where-i+text.size(); j++)
            {
                if((j>=0 && mainStr[j] != text[j-(where-i)]) || j<0 || j>=mainStr.size() || j>=text.size()) cool=false;
            }

            if(cool) return true;
        }
    }

    return false;
}

bool Fun::findText(std::string mainStr, std::string textToSearch, int where)
{
    if(where >= mainStr.size() || where<0) return false;
    if(mainStr.size() < textToSearch.size()) return false;

    bool cool=true;

    for(int i=where; i < where+textToSearch.size(); i++)
    {
        if(i>=mainStr.size() || mainStr[i]!=textToSearch[i-where])
        {
            cool=false;
            break;
        }
    }

    return cool;
}

std::string Fun::getTimeString(std::string mode)
{
    time_t tim;
    struct tm * taim;
    char stime[80];

    time(&tim);
    taim = localtime(&tim);

    strftime(stime, 80, mode.c_str(), taim);

    return (std::string)stime;
}

std::string Fun::reverseString(std::string str)
{
    std::string zum;
    for(int i=str.size()-1; i>=0; i--) zum.push_back(str[i]);
    return zum;
}

std::string Fun::getFileExtension(std::string filename)
{
    std::string temp;
    bool dotFound=false;

    for(int i=filename.size()-1; i>=0; i--)
    {
        if(filename[i]=='.')
        {
            dotFound=true;
            break;
        }
        temp.push_back(filename[i]);
    }

    if(dotFound) return reverseString(temp);
    return " ";
}

std::vector<std::string> Fun::stringToWordArray(std::string str)
{
    std::vector<std::string> woot;
    std::string tempo;

    for(int i=0; i<str.size(); i++)
    {
        if(str[i] != char(32)) tempo.push_back(str[i]);

        if(((str[i] == char(32)) || i==str.size()-1) && tempo.size()>0)
        {
            woot.push_back(tempo);
            tempo.clear();
        }
    }

    return woot;
}

bool Fun::isDivided(int64_t num, int64_t by_what)
{
    if(num % by_what == 0) return true;
    return false;
}

std::string Fun::getFilenameFromPath(std::string fap)
{
    std::string zam;
    for(int i=fap.size()-1; i>=0; i--)
    {
        if(fap[i]!='/' && fap[i]!=char(92))  zam.push_back(fap[i]);
        else break;
    }
    return reverseString(zam);
}

bool Fun::isSystemBigEndian()
{
     //int32_t t=-2147483648; //little endian 1 (100...0)
     uint32_t t=1;            //big endian 1    (000...1)
     if(t << 24) return true;
     return false;
}

//Standard func end.

//WinFuncs start:

#ifdef _WIN32
#include <windows.h>

std::string WinFun::GetOpenSaveFileWindows(int mode, const char filterLine[])
{
    OPENFILENAME ofn;
    TCHAR fname[ MAX_PATH ];
    std::string filename;

    ZeroMemory( &ofn , sizeof(ofn));

    ofn.lStructSize = sizeof ( ofn );
    ofn.hwndOwner = NULL ;
    ofn.lpstrFile = fname ;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof( fname );
    ofn.lpstrFilter = filterLine;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL ;
    ofn.nMaxFileTitle = 0 ;
    ofn.lpstrInitialDir = NULL ;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ;

    bool retval=false;

    if(mode==1) retval = GetOpenFileName(&ofn);
    else if(mode==2) retval = GetSaveFileName(&ofn);

    if(retval) filename=fname;
    else filename="No file selected.";

    return filename;
}

#endif // _WIN32

//WinFun End.
//end;
