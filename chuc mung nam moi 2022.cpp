//demo snake
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "console.h"

#define consoleWidth  80
#define consoleHeight 25
#define muitenlen		72
#define muitenxuong 	80
#define muitensangtrai 	75
#define muitensangphai	77
#define space			32
#define enter			13
#define ESC				27
#define chieucaokhung 25
#define chieurongkhung 40

enum TrangThai {UP, DOWN, LEFT, RIGHT};

struct ToaDo{
	int x, y; //y la tung do, x la hoanh do
	
};

struct HoaQua{
	ToaDo td;
};

struct Snake{
	ToaDo dot[31];
	int n;
	TrangThai tt;	
};

void KhoiTaoRan(Snake &snake, HoaQua &hq){
	snake.n = 1;
	snake.dot[0].x = 0;
	snake.dot[0].y = 0;
	snake.tt = RIGHT;
	
	hq.td.x = 10;
	hq.td.y = 10;
}

void HienThiRan(Snake snake, HoaQua &hq){
	clrscr();
	TextColor(15);
	for(int i = 0;i < chieucaokhung;i++){
		gotoXY(chieurongkhung, i);
		putchar(179);
	}
	TextColor(10);
	gotoXY(hq.td.x, hq.td.y);
	putchar('o');
	
	TextColor(rand()%15);
	gotoXY(snake.dot[0].x, snake.dot[0].y);
	putchar(2);
	
	for(int i = 0;i < snake.n;i++){
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		putchar('*');
	}
}

void DieuKhien_DiChuyenRan(Snake &snake){
	//truyen trang thai cua dot cu cho dot moi
	for(int i = snake.n - 1;i > 0;i--){
		snake.dot[i] = snake.dot[i - 1];
	}
	if(kbhit()){
		int key = _getch();
		if(key == 'A' || key == 'a' || key == muitensangtrai){
			snake.tt = LEFT;
		}
		else if(key == 'D' || key == 'd' || key == muitensangphai){
			snake.tt = RIGHT;
		}
		else if(key == 'W' || key == 'w' || key == muitenlen){
			snake.tt = UP;
		}
		else if(key == 'S' || key == 's' || key == muitenxuong){
			snake.tt = DOWN;
		}
	}
	if(snake.tt == UP){
		snake.dot[0].y--;
	}
	else if(snake.tt == DOWN){
		snake.dot[0].y++;
	}
	else if(snake.tt == LEFT){
		snake.dot[0].x--;
	}
	else if(snake.tt = RIGHT){
		snake.dot[0].x++;
	}
}
/*
tra ve 0 neu khong co gi
tra ve 1 neu thua game
*/
int XuLy(Snake &snake, HoaQua &hq){
	if(snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y){
		//an duoc hoa qua
		for(int i = snake.n;i > 0;i--){
			snake.dot[i] = snake.dot[i - 1];
		}
		snake.n++;
		if(snake.tt == UP){
			snake.dot[0].y--;
		}
		else if(snake.tt == DOWN){
			snake.dot[0].y++;
		}
		else if(snake.tt == LEFT){
			snake.dot[0].x--;
		}
		else if(snake.tt = RIGHT){
			snake.dot[0].x++;
		}
		
		hq.td.x = rand() % chieurongkhung;
		hq.td.y = rand() % chieucaokhung;
		
	}
	if(snake.dot[0].x < 0 || snake.dot[0].x >= chieurongkhung || snake.dot[0].y < 0 || snake.dot[0].y >= chieucaokhung){
		return -1;
	}
	for(int i = 1;i < snake.n;i++){
		if(snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y){
			return -1;
		}
	}
}

int main(){
	srand(time(NULL)); //khoi tao bo sinh so ngau nhien
	
	Snake snake;
	HoaQua hq;
	KhoiTaoRan(snake, hq);
	while(1){
		//hien thi
		HienThiRan(snake, hq);
		
		//dieu khien
		DieuKhien_DiChuyenRan(snake);
		//xu li
		
		if(XuLy(snake, hq) == -1){
			gotoXY(chieurongkhung + 1, 10);
			TextColor(10);
			printf("Nam moi vui ve!");
			while(_getch() != enter);z
			break;
		}
		
		//thua game, thang game
		Sleep(200);
	}
	clrscr();
}