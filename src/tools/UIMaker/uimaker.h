/*Windows Console UI v1.0 by H3nt4iBoY (C) 2015
- Features: color changer
- writing in specific positions
- Manipulating console cursor coordinates
- Custom input function, using several methods
- Sleep function

* Main Header
*/

#ifndef UIMAKER_H_INCLUDED
#define UIMAKER_H_INCLUDED

#include <iostream>
#include <string>
#include <windows.h>

#define POSITION_LEFT 1
#define POSITION_RIGHT 2
#define POSITION_CENTER 3
#define POSITION_CUSTOM 4

#define LINE_LENGHT 80

#define COLOR_WHITE 15
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_RED 4
#define COLOR_GRAY 8
#define COLOR_YELLOW 14
#define COLOR_DEFAULT -1
#define COLOR_BLACK 0

class UI
{
public:
    UI();
    ~UI();

    static void clearScreen();
    static void consoleGotoXY(int x, int y);
    static COORD getConsoleCursorCords();
    static void writeText(std::string text, int position=POSITION_LEFT, int x=0, int y=0);
    static std::string getUserInput(bool useGetline=false, bool useCinIgnore=false, bool customColor=false, int txtColor= COLOR_WHITE, int bgColor= COLOR_BLACK);
    static void fillWithChar(char c, int howMany);
    static void setColor(int textColor=COLOR_WHITE, int backgroundColor=0);
    static void sleep(int millisecs){ Sleep(millisecs); }
    static int getCurrentConsoleColor();
};


#endif // UIMAKER_H_INCLUDED
