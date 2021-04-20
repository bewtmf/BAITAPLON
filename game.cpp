#include<stdio.h>
#include <conio.h>
#include<Windows.h>

#define consoleWidth 80
#define consoleHeight 25
#define Road 25

void clrscr()
{
    CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void gotoXY(int x, int y)
{
    COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

struct Toado{
    int y, x;
};
struct Hinhdang{
    char a[3][3];
};

struct Car{
    Toado td;
    Hinhdang hd;
};
void TaoHinh(Car &xe){
    #define HD xe.hd.a
    xe.td.y = consoleHeight -2;
    xe.td.x = Road / 2;

    HD[0][0] = HD[0][2] = HD[2][0] = HD[2][2] = 'o';
    HD[0][1] = '^';
    HD[1][0] = HD[1][2] = '|'; HD[1][1] = ' ';
    HD[2][1]='-';
    
}
void Hienthi(Car xe){
    clrscr();
    for(int i=0;i < consoleHeight; i++)
        printf("%c\n",179);

    for(int i=0;i < consoleHeight; i++)
    {
        gotoXY(Road, i);
        putchar(179);
    }
    for(int kDong = -1; kDong <= 1; kDong++)
    {
        for(int kCot = -1; kCot <=1; kCot++)
            {
                int x = kCot + xe.td.x;
                int y = kDong + xe.td.y;
                gotoXY(x ,y);
                putchar(xe.hd.a[kDong+1][kCot+1]);
            }
    }
}
int main()
{   
    Car xe;
    TaoHinh(xe);
    while(1){
        clrscr();
        Hienthi(xe);

        Sleep(500);
    }


    system("pause");
    return 0;
}