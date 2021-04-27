#include <stdio.h>
#include<Windows.h>
#include<conio.h>

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

void gotoxy(int x, int y)
{
    COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void TextColor(int x){
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void cursor(BOOL bVisible, DWORD dwSize)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfor;
	ConsoleCursorInfor.bVisible = bVisible;
	ConsoleCursorInfor.dwSize = dwSize;
	SetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfor);
}

void Menu(){
	TextColor(10);
	gotoxy(30, 1); printf("##    ## ######## ######## ######## ");
	gotoxy(30, 2); printf("###   ## ##       ##       ##     ##");
	gotoxy(30, 3); printf("####  ## ##       ##       ##     ##");
    	gotoxy(30, 4); printf("## ## ## ######   ######   ##     ##");
    	gotoxy(30, 5); printf("##  #### ##       ##       ##     ##");	
	gotoxy(30, 6); printf("##   ### ##       ##       ##     ##");
	gotoxy(30, 7); printf("##    ## ######## ######## ######## ");

	TextColor(13);
	gotoxy(1, 10); printf("########  #######  ######## ");
	gotoxy(1, 11); printf("##       ##     ## ##     ##");
	gotoxy(1, 12); printf("##       ##     ## ##     ##");
	gotoxy(1, 13); printf("######   ##     ## ########");
	gotoxy(1, 14); printf("##       ##     ## ##   ##");
	gotoxy(1, 15); printf("##       ##     ## ##    ##");
	gotoxy(1, 16); printf("##        #######  ##     ##");

	TextColor(12);
	gotoxy(40, 10); printf(" ######  ########  ######## ######## ######## ");
	gotoxy(40, 11); printf("##    ## ##     ## ##       ##       ##     ##");
	gotoxy(40, 12); printf("##       ##     ## ##       ##       ##     ## ");
	gotoxy(40, 13); printf(" ######  ########  ######   ######   ##     ##");
	gotoxy(40, 14); printf("      ## ##        ##       ##       ##     ##");
	gotoxy(40, 15); printf("##    ## ##        ##       ##       ##     ##");
	gotoxy(40, 16); printf(" ######  ##        ######## ######## ######## ");

	gotoxy(20, 18); TextColor(10); printf("1. "); TextColor(15); printf("Start Game");
	gotoxy(20, 19); TextColor(10); printf("2. "); TextColor(15); printf("Tutorial");
	gotoxy(20, 20); TextColor(10); printf("3. "); TextColor(15); printf("Exit");

}

void gameover(){
	TextColor(12);
    	gotoxy(60,10); printf(" ######  	   ###   	##     ##	######## ");
    	gotoxy(60,11); printf("##    ## 	  ## ##  	###   ###	##       ");
    	gotoxy(60,12); printf("##       	 ##   ## 	#### ####	##       ");
    	gotoxy(60,13); printf("##   ####	##     ##	## ### ##	######   ");
	gotoxy(60,14); printf("##    ## 	#########	##     ##	##       ");
	gotoxy(60,15); printf("##    ## 	##     ##	##     ##	##       ");
	gotoxy(60,16); printf(" ######  	##     ##	##     ##	######## ");

	gotoxy(60,18); printf(" ####### 	##     ##	######## 	######## ");
	gotoxy(60,19); printf("##     ##	##     ##	##       	##     ##");
	gotoxy(60,20); printf("##     ## 	##     ##	##       	##     ##");
	gotoxy(60,21); printf("##     ## 	##     ##	######    	######## ");
	gotoxy(60,22); printf("##     ##	 ##   ## 	##        	##   ##  ");
	gotoxy(60,23); printf("##     ##	  ## ##  	##       	##    ## ");
	gotoxy(60,24); printf(" ####### 	   ###   	######## 	##     ##");
	TextColor(14);
	gotoxy(55,26); printf("Press 'ESC' to back to menu");
}

void Tutorial(){
	TextColor(11);
	gotoxy(5,2); printf("######## 	##     ##	######## 	 ####### 	######## 	#### 	   ###   	##       ");
	gotoxy(5,3); printf("   ##    	##     ##	   ##   	##     ##	##     ##	 ##  	  ## ##  	##       ");
	gotoxy(5,4); printf("   ##    	##     ##	   ##   	##     ##	##     ##	 ##  	 ##   ## 	##       ");
	gotoxy(5,5); printf("   ##    	##     ##	   ##   	##     ##	######## 	 ##  	##     ##	##       ");
	gotoxy(5,6); printf("   ##    	##     ##	   ##   	##     ##	##   ##  	 ##  	#########	##       ");
	gotoxy(5,7); printf("   ##    	##     ##	   ##   	##     ##	##    ## 	 ##  	##     ##	##       ");
	gotoxy(5,8); printf("   ##    	 ####### 	   ##   	 ####### 	##     ##	#### 	##     ##	######## ");

	gotoxy(10, 15); TextColor(14); printf("%c\t%c: ", 27, 26);  TextColor(10); printf("Move");
	gotoxy(10, 16); TextColor(14); printf("SPACEBAR: ");	TextColor(10); printf("Shoot bullet");
	gotoxy(40, 15); TextColor(4); printf("‼‼");
	gotoxy(40, 16); TextColor(4); printf("‼‼"); TextColor(10); printf(" = 2 POINTS");
	gotoxy(40, 17); TextColor(4); printf("‼‼");
	gotoxy(10, 18); TextColor(12); printf("Press 'ESC' to back to menu");
}
