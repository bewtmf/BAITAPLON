#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include "Menu.cpp"

#define consoleWidth 120
#define consoleHeight 30
#define Road 50

enum trangthai {UP, DOWN};

struct A{
    char kytu;
    int mau;
};
A buffer[consoleHeight][Road];
void Draw(int dong, int cot, int kytu, int mau){
    buffer[dong][cot].kytu = kytu;
    buffer[dong][cot].mau = mau;
}

struct Toado{
    int x, y;
};

struct Hinhdang{
    char a[3][3];
};

typedef struct Vehicle{
    Toado td;
    Hinhdang hd;
    int diem, level, luongmau;
    trangthai tt;
}Veh;

void TaoHinh(Veh &xe){
    #define HD xe.hd.a
    xe.td.y = consoleHeight -2;
    xe.td.x = Road / 2;

    HD[0][0] = HD[0][2] = HD[2][0] = HD[2][2] = 'o';
    HD[0][1] = '^';
    HD[1][0] = HD[1][2] = '|'; HD[1][1] = 'X';
    HD[2][1]='-';
}

void TaoVC(Veh vc[]){
    // Tạo 5 vật cản khác nhau theo 5 levels, level càng cao máu càng nhiêu
}

void Hienthi(Veh xe){
    // ve bien
    for(int i= 0;i< consoleHeight; i++)
    {
        Draw(i, 1, 219, 1);
        Draw(i, Road, 219, 1);
    }
    // ve xe
    for(int kDong = -1; kDong <= 1; kDong++)
    {
        for(int kCot = -1; kCot <= 1; kCot++)
            {
                int x = kCot + xe.td.x;
                int y = kDong + xe.td.y;
                Draw(y, x, xe.hd.a[kDong+1][kCot+1], 13);
            }
    }

    //** Dua buffer ra console **
    gotoxy(0, 0);
    for(int i = 0; i < consoleHeight; i++)
    {
        for(int j = 0;j < Road + 1; j++)
        {
            TextColor(buffer[i][j].mau);
            putchar(buffer[i][j].kytu);

            buffer[i][j].kytu = ' ';
        }
        if(i < consoleHeight - 1)
            putchar('\n');
    }

}

void Dieukhien(Veh &xe){
    if(kbhit())
    {
        int key = getch();
        if(key == 75 && xe.td.x > 3)
            xe.td.x--;
        else if(key == 77 && xe.td.x < Road - 2)
            xe.td.x++;
    }
}

int main()
{   
    cursor(0, 25);
    Veh xe;
    TaoHinh(xe);
    //khoi tao buffer
    for(int i=0;i< consoleHeight; i++)
        for(int j=0;j<Road;j++)
        {
            buffer[i][j].kytu = ' ';
            buffer[i][j].mau = 7;
        }
    int key;
    while(key!=27)
    {
        Hienthi(xe);
        Dieukhien(xe);
        printf("ESC to exit");
        key = getch();
    }

    return 0;
}