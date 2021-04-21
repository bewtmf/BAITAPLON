#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include "Menu.cpp"

#define consoleWidth 80
#define consoleHeight 25


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
    xe.td.x = consoleWidth / 2;

    HD[0][0] = HD[0][2] = HD[2][0] = HD[2][2] = 'o';
    HD[0][1] = '^';
    HD[1][0] = HD[1][2] = '|'; HD[1][1] = 'X';
    HD[2][1]='-';
}

void Hienthi(Car xe){
    clrscr();
    for(int kDong = -1; kDong <= 1; kDong++)
    {
        for(int kCot = -1; kCot <= 1; kCot++)
            {
                int x = kCot + xe.td.x;
                int y = kDong + xe.td.y;
                gotoXY(x ,y);
                putchar(xe.hd.a[kDong+1][kCot+1]);
            }
    }
    for(int i=0; i < consoleHeight; i++)
    {
        gotoXY(25,i);
        putchar(179);
    }
    for(int i=0; i < consoleHeight; i++)
    {
        gotoXY(55, i);
        putchar(179);
    }
    for(int i= 0; i < consoleHeight - 4;i++)
    {
        gotoXY(40,i);
        printf(".\n\n");
    }
}

void Dieukhien(Car &xe){
    if(kbhit())
    {
        int key = getch();
        if(key == 75 && xe.td.x > 27)
            xe.td.x--;
        else if(key == 77 && xe.td.x < 53)
            xe.td.x++;
    }
}
int main()
{   
    Car xe;
    TaoHinh(xe);
    while(1)
    {
        Hienthi(xe);
        Dieukhien(xe);

        Sleep(200);
    }


    return 0;
}