/*Windows Console UI v1.0 by H3nt4iBoY (C) 2015
-CPP 1
*/

#include "uimaker.h"

UI::UI(){ }

UI::~UI(){ }

void UI::clearScreen()
{
    system("cls");
}

void UI::consoleGotoXY(int x, int y)
{
    COORD cor={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

COORD UI::getConsoleCursorCords()
{
    COORD cord{0,0};
    CONSOLE_SCREEN_BUFFER_INFO bufinf;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufinf)) return cord;

    cord.X = bufinf.dwCursorPosition.X;
    cord.Y = bufinf.dwCursorPosition.Y;

    return cord;
}

int UI::getCurrentConsoleColor()
{
    CONSOLE_SCREEN_BUFFER_INFO bufinf;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufinf)) return COLOR_WHITE;

    return (int)bufinf.wAttributes;
}

void UI::setColor(int textColor, int backgroundColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor+16*backgroundColor);
}

void UI::writeText(std::string text, int pos, int x, int y)
{
    int nupos=0;

    switch(pos)
    {
    case POSITION_LEFT:
        std::cout<<text;
        break;
    case POSITION_RIGHT:
        nupos=LINE_LENGHT-text.size();
        if(nupos>0) consoleGotoXY(nupos, getConsoleCursorCords().Y);
        std::cout<<text;
        break;
    case POSITION_CENTER:
        nupos=(LINE_LENGHT-text.size())/2;
        if(nupos>0) consoleGotoXY(nupos, getConsoleCursorCords().Y);
        std::cout<<text;
        break;

    case POSITION_CUSTOM:
        consoleGotoXY(x,y);
        std::cout<<text;
        break;

    case POSITION_RIGHT | POSITION_CUSTOM:
        nupos=LINE_LENGHT-text.size();
        if(nupos>0) consoleGotoXY(nupos, y);
        std::cout<<text;
        break;
    case POSITION_CENTER | POSITION_CUSTOM:
        nupos=(LINE_LENGHT-text.size())/2;
        if(nupos>0) consoleGotoXY(nupos, y);
        std::cout<<text;
        break;
    default:
        std::cout<<text;
        break;
    }
}

void UI::fillWithChar(char c, int howMany)
{
    for(int i=0; i<howMany; i++) std::cout<<c;
}

std::string UI::getUserInput(bool useGetline, bool useCinIgnore, bool customColor, int txtColor, int bgColor)
{
    int lastc1,lastc2;
    if(customColor)
    {
        lastc1=getCurrentConsoleColor()%16;
        lastc2=getCurrentConsoleColor()/16;
        setColor(txtColor, bgColor);
    }
    std::string strr;
    if(useCinIgnore) std::cin.ignore();

    if(useGetline) std::getline(std::cin, strr);
    else std::cin>>strr;

    if(customColor) setColor(lastc1, lastc2);

    return strr;
}

//ends;
