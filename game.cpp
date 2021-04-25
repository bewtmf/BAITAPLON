#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include "Menu.cpp"

#define consoleWidth 120
#define consoleHeight 30
#define Road 50

enum trangthai{UP, DOWN, LEFT, RIGHT};

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
    int diem= 0, level;
    trangthai tt;
}Veh;

struct Dan{
    Toado td;
    trangthai tt;
    Hinhdang hd;
};

void TaoHinh(Veh &xe,Veh vc[],Dan dan){
    //khoi tao buffer
    for(int i=0;i< consoleHeight; i++)
        for(int j=0;j<Road;j++)
        {
            buffer[i][j].kytu = ' ';
            buffer[i][j].mau = 7;
        }

    //----Khởi tạo xe
    #define HD xe.hd.a
    xe.td.y = consoleHeight -2;
    xe.td.x = Road / 2;
    //--Vẽ xe
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
    //----Khởi tạo đạn
        dan.td.x = xe.td.x;
        dan.td.y = xe.td.y - 2;
        dan.tt = UP;
}

void Hienthi(Veh xe,Veh vc[],Dan dan){
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
    //---hiển thị đạn
        Draw(dan.td.y, dan.td.x, 'o', 6);
    //--- Hiển thị diểm và Levels
    xe.level = xe.diem / 10;
    gotoxy(Road + 2, 5);
        TextColor(14);
        printf("DIEM: ");
        TextColor(10);
        printf("%d",xe.diem);
    gotoxy(Road + 2, 6);
        TextColor(14);
        printf("LEVELS: "); TextColor(4);printf("%d",xe.level);
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

void Dichuyen(Veh &xe,Veh vc[],Dan &dan){
    //---Điều khiển xe
    if(_kbhit())
    {
        int key = getch();
        if(key == 75 && xe.td.x > 3)
            xe.td.x -= 2;
        else if(key == 77 && xe.td.x < Road -3)
            xe.td.x += 2;
    }

    for(int i = 0;i < 3; i++)
    {
        if(vc[i].tt == DOWN)
            vc[i].td.y++;
    }
    //---Đạn di chuyển
    if(dan.tt == UP)
    {
        dan.td.y -= 2;
    }
}

int Xuly(Veh &xe, Veh vc[],Dan &dan){
        // ******** Xử lý vật cản **********
    //----Xử lý chạm biên
    for(int i =0;i<3;i++)
    {
        if(vc[i].td.y > consoleHeight)
        {
            vc[i].td.x = 3 + rand() % (Road - 5);
            vc[i].td.y = rand() % (-2 - -6) + -2;
            xe.diem++;
        }
    }
    //----Vật cản va chạm xe
    int dX[3], dY[3];
    for(int i = 0;i<3;i++)
    {
        dX[i] = abs(xe.td.x - vc[i].td.x);
        dY[i] = abs(xe.td.y - vc[i].td.y);
        if(dX[i] < 3 && dY[i] < 3)
            {
                return -1;
            }
    }
        //****** Xử lý đạn ********
    //--- Reset đạn
    if(dan.td.y < 1)
    {
        dan.td.y = xe.td.y - 2;
        dan.td.x = xe.td.x;
    }
    //---Đạn va chạm vật cản
    int dx, dy;
    for(int i=0; i<3; i++)
    {
        dx = abs(dan.td.x - vc[i].td.x);
        dy = abs(dan.td.y - vc[i].td.y);
        if(dx < 2 && dy < 2)
        {
            xe.diem+=2;
            vc[i].td.x = 3 + rand() % (Road - 5);
            vc[i].td.y = -6;
            dan.td.x = xe.td.x;
            dan.td.y = xe.td.y - 2;
        }
    }

    return 0;
}

void Play(){
    clrscr();
    cursor(0, 25);
    srand(time(NULL));
    int timedelay = 500;
    Veh xe, vc[5];
    Dan dan;
    int ma = 0;
    TaoHinh(xe, vc, dan);
    while(1)
    {
        Hienthi(xe, vc, dan);
        Dichuyen(xe, vc, dan);
        ma = Xuly(xe, vc, dan);
        if(ma == -1){
            gameover();
            return;
        }
    }
}

int main()
{  
    int ext;
    cursor(0, 0);
    do{
        clrscr();
        Menu();
        char chon;
        do{
        gotoxy(10,30); printf("Ban chon: ");
        scanf("%c",&chon);
        }while(chon != '1' && chon != '2' && chon != '3');
        switch(chon)
        {
            case '1':
                Play();
                break;
            case '2':
                ext = 27;
        }
    }while(ext!=27);
    return 0;
}