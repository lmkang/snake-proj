// snake.cpp
// (C) 2015 ������

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h> 

using namespace std;

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define SNAKE_NODE_NUM 100

char game[MAP_WIDTH][MAP_HEIGHT];// ��Ϸ��ͼ
bool first = true;// ��Ϸ��ʼʱ����һ��
struct Snake
{
	int x, y;
	int length;
	char direction;// �ߵ��˶�����
	char newDirection;// ����µļ���Ӧ�ķ���
}snake[SNAKE_NODE_NUM];// �ߵĽṹ��
struct Food
{
	int x, y;
	int isFood;// 1 ��ʾ����ʳ��, 0 ����û��
}food;// ʳ��ṹ��

void initMap();// ��ʼ����ͼ
void onDraw();// ��ͼ�ػ�
void snakeMove();// �ߵ��ƶ�
void changeDirection(char);// ���̰�������Ӧ
bool isOppositeDir(char);
void randFood();// �������ʳ��
bool isSnakeDie();// �ж��ߵ�����
void setCursor(int x, int y);// �̶����,���ع��,������
void setConsoleStyle();// ���ô��ڷ��

int main()
{
	setConsoleStyle();
	initMap();// ��ʼ����ͼ
	srand((unsigned int)time(NULL));// ʱ������
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
			//�Ե�ʳ������Ӧ
			if(snake[0].x == food.x && snake[0].y == food.y)
			{
				snake[0].x = food.x;
				snake[0].y = food.y;
				snake[0].length++;
				food.isFood = 0;
				randFood();
			}
			if(isSnakeDie())//�ж����Ƿ�����
			{
				cout<<"�÷֣�"<<(snake[0].length-3)*10<<"   game over!"<<endl;
				system("pause");
				exit(0);
			}
			setCursor(0,0);//���̶�
			onDraw();//�ػ�
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
	//��ʼ����
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
	game[tail_x][tail_y] = ' ';//Ĩ����β

	if(!isOppositeDir(snake[0].newDirection)){// �ߵ��ƶ�����һ��Ҫ�������ƶ�ʱ��ȷ��
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

bool isOppositeDir(char dir){// �Ƿ����෴����
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

		bool flag = false;// ��ǲ�����ʳ���Ƿ��������ص�

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
	//ײǽ
	if(snake[0].x==0 || snake[0].x==MAP_WIDTH-1 || snake[0].y==0 || snake[0].y==MAP_HEIGHT)
	{
		return true;
	}
	//�Ե��Լ�
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
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//�õ�����̨���
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);//���ÿ���̨���λ��
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);// ��ȡ�����Ϣ
	cci.bVisible = FALSE;// ���ع�� 
	SetConsoleCursorInfo(hOut, &cci);// ���ù����Ϣ 
}

void setConsoleStyle()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// �õ�����̨��� 
	SetConsoleTitle("̰����V1.0  ����: WASD");// ���ÿ���̨���� 
	system("mode con cols=44 lines=22");
}
