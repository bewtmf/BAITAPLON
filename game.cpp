#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include "Menu.cpp"

#define consoleWidth 120
#define consoleHeight 30
#define Road 50

enum trangthai{UP, DOWN};

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
    int diem, level;
    trangthai tt;
}Veh;

void TaoHinh(Veh &xe,Veh vc[]){
    #define HD xe.hd.a
    xe.td.y = consoleHeight -2;
    xe.td.x = Road / 2;
    //--------Khởi tạo xe
    HD[0][0] = HD[0][2] = HD[2][0] = HD[2][2] = 'o';
    HD[0][1] = '^';
    HD[1][0] = HD[1][2] = '|'; HD[1][1] = 'X';
    HD[2][1]='-';
    //----Khởi tạo vật cản
    for(int i=0 ;i < 3;i ++)
    {
        vc[i].td.x = 3 + rand() % (Road - 5);
        vc[i].td.y = rand() % (-2 - -6) + -2;
        vc[i].tt = DOWN;
        for(int dong = 0;dong < 3; dong++)
        {
            for(int cot = 0; cot < 3; cot++)
              vc[i].hd.a[dong][cot] = 19;
        }
    }
}



void Hienthi(Veh xe,Veh vc[]){
    //------Vẽ đường biên
    for(int i= 0;i< consoleHeight; i++)
    {
        Draw(i, 1, 219, 1);
        Draw(i, Road, 219, 1);
    }
    //-----Vẽ xe
    for(int dong = -1; dong <= 1; dong++)
    {
        for(int cot = -1; cot <= 1; cot++)
            {
                int x = cot + xe.td.x;
                int y = dong + xe.td.y;
                Draw(y, x, xe.hd.a[dong+1][cot+1], 13);
            }
    }

    //---Vẽ vật cản
    for(int i =0 ;i < 3;i ++)
    {
        for(int dong = -1; dong <= 1; dong++)
        {
            for(int cot = -1; cot <= 1; cot ++)
            {
                int x = cot + vc[i].td.x;
                int y = dong + vc[i].td.y;
                if(y >= 0 && y < consoleHeight)
                    Draw(y, x, vc[i].hd.a[dong+1][cot+1], 4);
            }

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

void Dichuyen(Veh &xe,Veh vc[]){
    //---Điều khiển xe
    if(_kbhit())
    {
        int key = getch();
        if(key == 75 && xe.td.x > 3)
            xe.td.x -=2;
        else if(key == 77 && xe.td.x < Road -3)
            xe.td.x +=2;
    }
    //---Vật cản di chuyển
    for(int i = 0;i < 3; i++)
    {
        if(vc[i].tt == DOWN)
            vc[i].td.y++;
    }
}

int Xuly(Veh &xe, Veh vc[]){
    //----Xử lý chạm biên
    for(int i =0;i<3;i++)
    {
        if(vc[i].td.y > consoleHeight)
        {
            vc[i].td.x = 3 + rand() % (Road - 5);
            vc[i].td.y = rand() % (-2 - -6) + -2;
        }
    }
    //----Xử lý va chạm
    int dX = 0, dY = 0;
    for(int i =0;i<3;i++)
    {
        dX = abs(xe.td.x - vc[i].td.x);
        dY = abs(xe.td.y - vc[i].td.y);
        if(dX < 3 && dY < 3)
        {
            while(getch() !=13)
                return -1;
        }
        return 0;
    }
    return 0;
}
int main()
{  
    cursor(0, 25);
    srand(time(NULL));
    Veh xe, vc[5];
    int timedelay = 50;
    TaoHinh(xe, vc);
    //khoi tao buffer
    for(int i=0;i< consoleHeight; i++)
        for(int j=0;j<Road;j++)
        {
            buffer[i][j].kytu = ' ';
            buffer[i][j].mau = 7;
        }
    while(1)
    {
        Hienthi(xe, vc);
        Dichuyen(xe, vc);
        Xuly(xe, vc);

        Sleep(timedelay);
    }
    return 0;
}