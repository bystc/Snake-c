#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.h>
#include<time.h>
char x[10][20];
int ROW[20];//横坐标
int COL[20];//纵坐标
int food_row, food_col;//分别代表横纵坐标
char ch = 'd';
int len = 3;
char f;
void getFood()//食物
{
	food_row = rand() % 10;
	food_col = rand() % 20;
	if (x[food_row][food_col] == 79)
	{
		getFood();
	}
	else
		x[food_row][food_col] = 42;
}
void print()
{
	for (int i = 0; i < len; i++)//将数组中记录的蛇身坐标全部填充为笑脸，其ASCII码为1；
	{
		x[ROW[i]][COL[i]] = 79;
	}
	for (int i = 0; i < 10; i++)//用遍历的形式绘制
	{
		for (int j = 0; j < 20; j++)
		{
			printf("%c", x[i][j]);
		}
		printf("\n");
	}
	Sleep(500);//休眠0.5秒 相当于蛇0.5秒动一下
	system("cls");//清屏函数。。以便将蛇身重新绘制
}
void getkey()//判断是否按下键盘
{
	if (_kbhit())//如果按下键盘，就会执行以下语句
	{
		ch = _getch();//获取键盘值
		if (ch == f)//如果这次按键和现在走的方向一致则为无效按键，重新来获取按下的键盘值
		{
			getkey();
		}
		else if ((ch == 100 && f != 97) || ch == 119 && f != 115 || ch == 97 && f != 100 || ch == 115 && f != 119) //即来判断其他无效按键（即朝左走时不能让其朝右走等等）
			f = ch;//按键有效时将ch赋值为f
		else
			getkey();//按键无效时重新捕获键盘
	}
}
void left()
{
	x[ROW[0]][COL[0]] = '-';
	for (int i = 0; i < len - 1; i++)//蛇身全部前进一格
	{
		COL[i] = COL[i + 1];
		ROW[i] = ROW[i + 1];
	}
	COL[len - 1]--;
}
void right()
{
	x[ROW[0]][COL[0]] = '-';
	for (int i = 0; i < len - 1; i++)//蛇身全部前进一格
	{
		COL[i] = COL[i + 1];
		ROW[i] = ROW[i + 1];
	}
	COL[len - 1]++;
}
void up()
{
	x[ROW[0]][COL[0]] = '-';
	for (int i = 0; i < len - 1; i++)//蛇身全部前进一格
	{
		COL[i] = COL[i + 1];
		ROW[i] = ROW[i + 1];
	}
	ROW[len - 1]--;
}
void down()
{
	x[ROW[0]][COL[0]] = '-';
	for (int i = 0; i < len - 1; i++)//蛇身全部前进一格
	{
		COL[i] = COL[i + 1];
		ROW[i] = ROW[i + 1];
	}
	ROW[len - 1]++;
}
bool judge() {
	for (int i = 0;i < len - 1;i++) {
		if (ROW[len - 1] == ROW[i] && COL[len - 1] == COL[i]) {
			return false;
		}
	}
	return true;
}
int main()
{
	f = ch;//将初始的移动方向赋值给f
	for (int i = 0; i < 10; i++) //将字符数组全部以'-'填充，进行初始化
	{
		for (int j = 0; j < 20; j++)
		{
			x[i][j] = '-';
		}
	}
	for (int i = 0; i < 10; i++)//将储存坐标的数组全部归零
	{
		COL[i] = 0;
		ROW[i] = 0;
	}
	for (int i = 0; i < len; i++)//记录前3个蛇身坐标
		ROW[i] = i;
	getFood();
	while (len <= 19)//设置蛇的最大长度来赢得游戏
	{
		getkey();
		if (x[food_row][food_col] != 42)//食物没有了才获取食物
		{
			getFood();
		}
		switch (f)
		{
		case 'w':
			if (ROW[len - 1] - 1 < 0)
			{
				printf("碰到上墙了\n");
				return 0;
			}
			else if (ROW[len - 1] - 1 == food_row && COL[len - 1] == food_col)//判断蛇要走的下个点是否是食物的点
			{
				ROW[len] = food_row;
				COL[len] = food_col;
				len++;
				break;
			}
			up();
			break;
		case 'a':
			if (COL[len - 1] - 1 < 0)
			{
				printf("碰到左墙了\n");
				return 0;
			}
			else if (ROW[len - 1] == food_row && COL[len - 1] - 1 == food_col)
			{
				ROW[len] = food_row;
				COL[len] = food_col;
				len++;
				break;
			}
			left();
			break;
		case 's':
			if (ROW[len - 1] + 1 >= 10)
			{
				printf("碰到下墙了\n");
				return 0;
			}
			if (ROW[len - 1] + 1 == food_row && COL[len - 1] == food_col)
			{
				ROW[len] = food_row;
				COL[len] = food_col;
				len++;
				break;
			}
			down();
			break;
		case 'd':
			if (COL[len - 1] + 1 >= 20)
			{
				printf("碰到右墙了\n");
				return 0;
			}
			if (ROW[len - 1] == food_row && COL[len - 1] + 1 == food_col)
			{
				ROW[len] = food_row;
				COL[len] = food_col;
				len++;
				break;
			}
			right();
			break;
		}
		if (!judge()) {
			printf("你吃到自己了\n");
			return 0;
		}
		print();
	}
	printf("You win!\n");
	system("pause");
	return 0;
}
