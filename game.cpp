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
    int diem= 0;
    trangthai tt;
}Veh;

struct Dan{
    Toado td;
    trangthai tt;
    Hinhdang hd;
};

void TaoHinh(Veh &xe,Veh vc[]){
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
    for(int i=0 ;i < 6; i++)
    {  
        vc[i].td.x = 3 + rand() % (Road - 5); // x[2, 27];
        vc[i].td.y = rand() % (-2 + 6) - 2; // y[-2, -6]; rand() % (max - min) + min;
        vc[i].tt = DOWN;
        for(int dong = 0;dong < 3; dong++)
        {
            for(int cot = 0; cot < 3; cot++)
            {
                if(i < 3)
                    vc[i].hd.a[dong][cot] = 19; // tạo hình cho xe 1 -> 3
                else if( i >= 3)
                    vc[i].hd.a[dong][cot] = 207; // tạo hình cho xe 4, xe 5
            }
        }
    }
}

void Hienthi(Veh xe,Veh vc[], Dan dan){
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
                Draw(y, x, xe.hd.a[dong+1][cot+1], 11);
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
    if(xe.diem >= 50)
    {
        for(int i = 3 ;i < 6;i ++)
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
    }
    //---hiển thị đạn
    if(dan.tt == UP)
        Draw(dan.td.y, dan.td.x, 'o', 6);
    //--- Hiển thị diểm
    gotoxy(Road + 2, 4);
        TextColor(10);
        printf("SPACEBAR"); TextColor(14); printf(" :Shoot bullet");
    gotoxy(Road + 2, 5);
        TextColor(10);
        printf("POINTS: ");
        TextColor(14);
        printf("%d",xe.diem);
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

void Dichuyen(Veh &xe,Veh vc[], Dan &dan){
    //---Điều khiển xe
    if(_kbhit())
    {
        int key = getch();
        if(key == 75 && xe.td.x > 3)
            xe.td.x -= 2;
        else if(key == 77 && xe.td.x < Road -3)
            xe.td.x += 2;
        if(key == 32)
        {
            dan.td.x = xe.td.x;
            dan.td.y = xe.td.y - 2;
            dan.tt = UP;
        }
    }
    //---Vật cản di chuyển
    for(int i = 0;i < 3; i++)
    {
        if(vc[i].tt == DOWN)
            vc[i].td.y++;
    }
    if(xe.diem >= 50)
    {
        for(int i= 3; i < 6; i++)
        {
            if(vc[i].tt == DOWN)
                vc[i].td.y +=2;
        }
    }
    //---Đạn di chuyển
    if(dan.tt == UP)
    {
        dan.td.y -= 2;
    }
}

int Xuly(Veh &xe, Veh vc[], Dan &dan){
        // ******** Xử lý vật cản **********
    //----Xử lý chạm biên
    for(int i = 0; i < 3; i++)
    {
        if(vc[i].td.y > consoleHeight)
        {
            vc[i].td.x = 3 + rand() % (Road - 5);
            vc[i].td.y = rand() % (-2 + 6) - 2;
            xe.diem++;
        }
    }
    for(int i = 3; i < 6; i++)
    {
        if(vc[i].td.y > consoleHeight)
        {
            vc[i].td.x = 3 + rand() % (Road - 5); // random(3, 28)
            vc[i].td.y = rand() % (-4 + 10) - 4; // random(-4, -10)
            xe.diem++;
        }
    }
    //----Vật cản va chạm xe
    int dX[5], dY[5];
    for(int i = 0; i < 3;i++)
    {
        dX[i] = abs(xe.td.x - vc[i].td.x);
        dY[i] = abs(xe.td.y - vc[i].td.y);
        if(dX[i] < 3 && dY[i] < 3)
                return -1;
    }
    for(int i = 3; i < 6; i++)
        {
            dX[i] = abs (xe.td.x - vc[i].td.x);
            dY[i] = abs (xe.td.y - (vc[i].td.y - 1) );
            if(dX[i] < 3 && dY[i] < 3)
                return -1;  
        }
        //****** Xử lý đạn ********
    //--- Reset đạn
    if(dan.td.y < 0)
    {
        dan.td.x = 0;
        dan.td.y = 0; // giấu đạn khi chạm biên
    }
    //---Đạn va chạm vật cản
    for(int i= 0; i < 3; i++)
    {
        int dx = abs(dan.td.x - vc[i].td.x);
        int dy = abs(dan.td.y - vc[i].td.y);
        if(dx < 2 && dy < 2)
        {
            xe.diem += 2;
            vc[i].td.x = 3 + rand() % (Road - 5);
            vc[i].td.y = rand() % (-2 - -6) + -2;
            dan.td.x = 0;
            dan.td.y = 0; // giấu đạn khi đạn va chạm vc
        }
    }
    for(int i = 3; i < 6; i++)
    {
        int dx = abs(dan.td.x - vc[i].td.x);
        int dy = abs(dan.td.y - (vc[i].td.y-1) );
        if(dx < 2 && dy < 2)
        {
            xe.diem +=2;
            vc[i].td.x = 3 + rand() % (Road - 5);
            vc[i].td.y = rand() % (-4 - -8) + -4;
            dan.td.x = 0;
            dan.td.y = 0;
        }
    }
    return 0;
}

void Play(){
    clrscr();
    cursor(0, 25);
    srand(time(NULL));
    Veh xe, vc[6];
    Dan dan;
    int ma = 0;
    TaoHinh(xe, vc);
    while(1)
    {
        Hienthi(xe, vc, dan);
        Dichuyen(xe, vc, dan);
        ma = Xuly(xe, vc, dan);
        if(ma == -1){
            int key;
            while(key!=27)
            {
                gameover();
                key=getch();
            }
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
        gotoxy(10,25); printf("You choose: ");
        scanf("%c",&chon);
        }while(chon != '1' && chon != '2' && chon != '3');
        switch(chon)
        {
            case '1':
                Play();
                break;
            case '2':
                int key;
                do{
                    clrscr();
                    Tutorial();
                    key = getch();
                }while(key != 27);
                break;
            case '3':
                ext = 27;
        }
    }while(ext!=27);
    return 0;
}