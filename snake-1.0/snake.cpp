// snake.cpp
// (C) 2015 梁明康

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h> 

using namespace std;

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define SNAKE_NODE_NUM 100

char game[MAP_WIDTH][MAP_HEIGHT];// 游戏地图
bool first = true;// 游戏开始时清屏一次
struct Snake
{
	int x, y;
	int length;
	char direction;// 蛇的运动方向
	char newDirection;// 最后按下的键对应的方向
}snake[SNAKE_NODE_NUM];// 蛇的结构体
struct Food
{
	int x, y;
	int isFood;// 1 表示已有食物, 0 代表没有
}food;// 食物结构体

void initMap();// 初始化地图
void onDraw();// 地图重画
void snakeMove();// 蛇的移动
void changeDirection(char);// 键盘按键的响应
bool isOppositeDir(char);
void randFood();// 随机产生食物
bool isSnakeDie();// 判断蛇的死亡
void setCursor(int x, int y);// 固定光标,隐藏光标,防闪屏
void setConsoleStyle();// 设置窗口风格

int main()
{
	setConsoleStyle();
	initMap();// 初始化地图
	srand((unsigned int)time(NULL));// 时间种子
	randFood();
	onDraw();
	char keydown;
	while(true)
	{
		keydown = getch();	
		changeDirection(keydown);	
		if(first)
		{
			system("cls");
			first = false;
		}
		while(!kbhit())
		{
			snakeMove();
			//吃到食物后的响应
			if(snake[0].x == food.x && snake[0].y == food.y)
			{
				snake[0].x = food.x;
				snake[0].y = food.y;
				snake[0].length++;
				food.isFood = 0;
				randFood();
			}
			if(isSnakeDie())//判断蛇是否死了
			{
				cout<<"得分："<<(snake[0].length-3)*10<<"   game over!"<<endl;
				system("pause");
				exit(0);
			}
			setCursor(0,0);//光标固定
			onDraw();//重画
			Sleep(200);
		}
	}
	return 0;
}

void initMap()
{
	for(int i = 0; i<MAP_WIDTH; i++)
	{
		for(int j = 0; j<MAP_HEIGHT; j++)
		{
			if(i==0 || i==MAP_WIDTH-1 || j==0 || j==MAP_HEIGHT-1)
				game[i][j] = '*';
			else
				game[i][j] = ' ';
		}
	}
	//初始化蛇
	snake[0].x = (MAP_WIDTH/2)-2, snake[0].y = (MAP_HEIGHT/2)-2;
	snake[1].x = (MAP_WIDTH/2)-2, snake[1].y = (MAP_HEIGHT/2)-1;
	snake[2].x = (MAP_WIDTH/2)-2, snake[2].y = MAP_HEIGHT/2;
	snake[0].length = 3;
	snake[0].direction = 'a';
	snake[0].newDirection = 'a';
	food.isFood = 0;
	game[snake[0].x][snake[0].y] = '*';
	game[snake[1].x][snake[1].y] = '*';
	game[snake[2].x][snake[2].y] = '*';
}

void onDraw()
{
	for(int i = 0; i<snake[0].length; i++)
	{
		game[snake[i].x][snake[i].y] = '*';
	}
	for(int j = 0; j<MAP_WIDTH; j++)
	{
		for(int k = 0; k<MAP_HEIGHT; k++)
			cout<<game[j][k]<<' ';
		cout<<endl;
	}
}

void snakeMove()
{
	int tail_x = snake[snake[0].length-1].x;
	int tail_y = snake[snake[0].length-1].y;
	game[tail_x][tail_y] = ' ';//抹掉蛇尾

	if(!isOppositeDir(snake[0].newDirection)){// 蛇的移动方向一定要在真正移动时才确定
		snake[0].direction = snake[0].newDirection;
	}

	for(int i = snake[0].length-1; i>0; i--)
	{
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	switch(snake[0].direction)
	{
	case 'w':
		snake[0].x--;
		break;
	case 'a':
		snake[0].y--;
		break;
	case 's':
		snake[0].x++;
		break;
	case 'd':
		snake[0].y++;
		break;
	default:
		break;
	}
}

void changeDirection(char key)
{
	switch(key)
	{
	case 'w':
	case 'W':	
		snake[0].newDirection = 'w';		
		break;
	case 'a':
	case 'A':	
		snake[0].newDirection = 'a';		
		break;
	case 's':
	case 'S':		
		snake[0].newDirection = 's';		
		break;
	case 'd':
	case 'D':	
		snake[0].newDirection = 'd';		
		break;
	}
}

bool isOppositeDir(char dir){// 是否是相反方向
	bool result = false;
	switch(dir)
	{
	case 'w':
	case 'W':
		if(snake[0].direction == 's')
		{
			result = true;
		}
		break;
	case 'a':
	case 'A':
		if(snake[0].direction == 'd')
		{
			result = true;
		}
		break;
	case 's':
	case 'S':
		if(snake[0].direction == 'w')
		{
			result = true;
		}
		break;
	case 'd':
	case 'D':
		if(snake[0].direction == 'a')
		{
			result = true;
		}
		break;
	}
	return result;

}

void randFood()
{
	if(food.isFood == 0)
	{
		food.x = rand()%(MAP_WIDTH-2) + 1;
		food.y = rand()%(MAP_HEIGHT-2) + 1;

		bool flag = false;// 标记产生的食物是否与蛇身重叠

		while(true)
		{
			for(int i = 0; i < snake[0].length; i++)
			{
				if(snake[i].x==food.x && snake[i].y==food.y)
				{
					food.x = rand()%(MAP_WIDTH-2) + 1;
					food.y = rand()%(MAP_HEIGHT-2) + 1;
					flag = true;
					break;
				}
			}
			if(!flag)
			{
				break;
			}
			flag = false;
		}

		game[food.x][food.y] = '*';
		food.isFood = 1;
	}
}

bool isSnakeDie()
{
	//撞墙
	if(snake[0].x==0 || snake[0].x==MAP_WIDTH-1 || snake[0].y==0 || snake[0].y==MAP_HEIGHT)
	{
		return true;
	}
	//吃到自己
	for(int i = snake[0].length-1; i>2; i--)
	{
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)
		{
			return true;
		}
	}
	return false;
}

void setCursor(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//得到控制台句柄
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);//设置控制台光标位置
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);// 获取光标信息
	cci.bVisible = FALSE;// 隐藏光标 
	SetConsoleCursorInfo(hOut, &cci);// 设置光标信息 
}

void setConsoleStyle()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 得到控制台句柄 
	SetConsoleTitle("贪吃蛇V1.0  按键: WASD");// 设置控制台标题 
	system("mode con cols=44 lines=22");
}
