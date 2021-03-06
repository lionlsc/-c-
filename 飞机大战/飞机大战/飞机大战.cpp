//项目名称：飞机大战
//制作人：lionlsc
//完成日期：2018-2-26
//所用图片音乐素材均来自网络
//基于c语言和easyx开发的一个小游戏
//开发平台：visual studio 2017
#include "stdafx.h"
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")
#define width 591
#define high 750
IMAGE bkphoto, plane1, plane2, enemy1[2], enemy2[2], mybullet1[2], mybullet2[2], enemybullet1[2], enemybullet2[2], explode1, explode2, gameover1, gameover2;
int bullet_v = 30; //敌机子弹速度	
int enemy_v = 10;  //敌机速度
int plane_v = 50;
int enemy_x[2], enemy_y[2]; //敌机坐标
int plane_x, plane_y;//玩家坐标
int bullet_x[2], bullet_y[2];//玩家发射子弹的坐标
int enemybulletx[2], enemybullety[2];//敌人子弹的坐标
int enemyexplode[2];//被子弹射中后敌机爆炸
int isenemyshoot[2],ishoot[2];//敌人是否发射子弹，玩家时候发射子弹
int score=0;//得分
int secondplane;//用于判断敌机出现
int initialize[2];//是否记录按下空格键时飞机的坐标
int end = 0;//结束游戏
void inital()
{
	initgraph(width, high);
	system("title 飞机大战");
	mciSendString("open D:\\gamesourse\\gamemusic.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	int i;
	loadimage(&bkphoto, "D:\\gamesourse\\background.jpg");
	loadimage(&plane1, "D:\\gamesourse\\plane1.jpg");
	loadimage(&plane2, "D:\\gamesourse\\plane2.jpg");
	loadimage(&explode1, "D:\\gamesourse\\planeExplode_1.jpg");
	loadimage(&explode2, "D:\\gamesourse\\planeExplode_2.jpg");
	loadimage(&gameover1,"D:\\gamesourse\\gameover1.jpg");
	loadimage(&gameover2, "D:\\gamesourse\\gameover2.jpg");
	for ( i = 0; i < 2; i++)
	{
		loadimage(&enemy1[i], "D:\\gamesourse\\enemyPlane1.jpg");
		loadimage(&enemy2[i], "D:\\gamesourse\\enemyPlane2.jpg");
		loadimage(&enemybullet1[i], "D:\\gamesourse\\bullet1.jpg");
		loadimage(&enemybullet2[i], "D:\\gamesourse\\bullet2.jpg");
		loadimage(&mybullet1[i], "D:\\gamesourse\\bullet1.jpg");
		loadimage(&mybullet2[i], "D:\\gamesourse\\bullet2.jpg");
	}
	plane_x = 243; plane_y = 552;
	srand(time(NULL));
	enemy_x[0] = rand() % 487;
	enemy_x[1] = rand() % 487;
	for (i = 0; i < 2; i++)
	{
		enemyexplode[i] = 0;
		isenemyshoot[i] = 0;
		enemy_y[i] = -148;
		enemybulletx[i] = -200;
		enemybullety[i] = -200;
		ishoot[i] = 0;
		initialize[i] = 0;
	}
}
void enemy()
{     
	if (enemyexplode[0]==0)                               
	{
		putimage(enemy_x[0], enemy_y[0], &enemy1[0], NOTSRCERASE);
		putimage(enemy_x[0], enemy_y[0], &enemy2[0], SRCINVERT);
		if ((enemy_y[0] >-60)&&(enemy_y[0]<-35))                  //当敌人飞机的坐标满足一定条件，发射子弹
		{
			enemybulletx[0] = enemy_x[0] + 42;
			enemybullety[0] = enemy_y[0] + 133;
			isenemyshoot[0] = 1;
		}
		if ((enemy_y[0]>90)&&(enemy_y[0]<125))               //当"第一架"飞机坐标满足一定条件，出现"第二架"飞机
		{
			secondplane = 1;
		}
		enemy_y[0] = enemy_y[0] + enemy_v;              //更新飞机坐标
	}
	if ((enemy_y[0]>750)&&(enemyexplode[0]==0))        //敌机飞出游戏界面
	{
		enemy_x[0] = rand() % 487;
		enemy_y[0] = -148;
	}
	if (isenemyshoot[0] = 1)                           //当敌人飞机的坐标满足一定条件，发射子弹
	{
		putimage(enemybulletx[0], enemybullety[0], &enemybullet1[0], NOTSRCERASE);
		putimage(enemybulletx[0], enemybullety[0], &enemybullet2[0], SRCINVERT);
		enemybullety[0] = enemybullety[0] + bullet_v;
		if ((enemybullety[0]>750))              //子弹飞出游戏画面
		{
			isenemyshoot[0] = 0;
		}
	}
	if ((secondplane==1)&&(enemy_y[1]<750)&&(enemyexplode[1]==0))          //第二架敌人飞机
	{
		putimage(enemy_x[1], enemy_y[1], &enemy1[1], NOTSRCERASE);
		putimage(enemy_x[1], enemy_y[1], &enemy2[1], SRCINVERT);
		if ((enemy_y[1]>-60)&&(enemy_y[1]<-35))                   //当敌人飞机的坐标满足一定条件，发射子弹
		{
			isenemyshoot[1] = 1;
			enemybulletx[1] = enemy_x[1] + 42;
			enemybullety[1] = enemy_y[1] + 133;
		}
		if ((enemy_y[1]>-60)&&(enemy_y[1]>-50))
		{
			isenemyshoot[1] = 1;
		}
		enemy_y[1] = enemy_y[1] + enemy_v;
	}
    if ((enemy_y[1]>750) && (enemyexplode[1] == 0))           //敌机飞出游戏界面
	{
		enemy_x[1] = rand() % 487;
		enemy_y[1] = -148;
		secondplane = 0;
	}
	if (isenemyshoot[1] = 1)                        //当敌人飞机的坐标满足一定条件，发射子弹
	{
		putimage(enemybulletx[1], enemybullety[1], &enemybullet1[1], NOTSRCERASE);
		putimage(enemybulletx[1], enemybullety[1], &enemybullet2[1], SRCINVERT);
		enemybullety[1] = enemybullety[1] + bullet_v;
		if (enemybullety[1]>750)                          //子弹飞出游戏画面
		{
			isenemyshoot[1] = 0;
		}
	}
}
void myplane()
{
	int i, temp = 0;
	char c, ch;
	putimage(plane_x, plane_y, &plane1, NOTSRCERASE);
	putimage(plane_x, plane_y, &plane2, SRCINVERT);
	if ((enemybulletx[0]>(plane_x - 9)) && (enemybulletx[0]<(plane_x + 95)) && ((enemybullety[0] - bullet_v)>(plane_y)) && ((enemybullety[0] - bullet_v)<(plane_y + 120)))         //子弹和飞机相撞
	{
		end = 1;
	}
	if ((enemybulletx[1]>(plane_x - 9)) && (enemybulletx[1]<(plane_x + 95)) && ((enemybullety[1] - bullet_v)>(plane_y)) && ((enemybullety[1] - bullet_v)<(plane_y + 120)))         //子弹和飞机相撞
	{
		end = 1;
	}
	if (((enemy_x[0])>(plane_x-104))&&((enemy_x[0])<(plane_x+95))&&((enemy_y[0]-enemy_v)>(plane_y-140))&&((enemy_y[0]-enemy_v)<(plane_y+120)))                                      //飞机相撞
	{
		end = 1;
	}
	if (((enemy_x[1])>(plane_x - 104)) && ((enemy_x[1])<(plane_x + 95)) && ((enemy_y[1] - enemy_v)>(plane_y - 140)) && ((enemy_y[1] - enemy_v)<(plane_y + 120)))                   //飞机相撞
	{
		end = 1;
	}
	if (end == 0)                                                       //更新玩家飞机坐标，以及发射子弹
	{
		if (kbhit())
		{
			ch = _getch();
			c = ch;
			if (ch == 'a')
			{
				plane_x = plane_x - plane_v;
				if (plane_x <= 0)
				{
					plane_x = 0;
				}
			}
			if (ch == 'd')
			{
				plane_x = plane_x + plane_v;
				if ((plane_x + 104) >= width)
				{
					plane_x = width - 104;
				}
			}
			if (ch == 's')
			{
				plane_y = plane_y + plane_v;
				if (plane_y + 148 >= high)
				{
					plane_y = high - 108;
				}
			}
			if (ch == 'w')
			{
				plane_y = plane_y - plane_v;
				if (plane_y <= 0)
				{
					plane_y = 0;
				}
			}
			if (ch == ' ')                           //玩家最多可以同时发射两颗子弹
			{
				if (ishoot[0] == 0)
				{
					mciSendString("close shootmusic", NULL, 0, NULL);
					mciSendString("open D:\\gamesourse\\f_gun.mp3 alias shootmusic", NULL, 0, NULL);
					mciSendString("play shootmusic", NULL, 0, NULL);
					ishoot[0] = 1;
					initialize[0] = 1;
				}
				else if (ishoot[1] == 0)
				{
					mciSendString("close shootmusic", NULL, 0, NULL);
					mciSendString("open D:\\gamesourse\\f_gun.mp3 alias shootmusic", NULL, 0, NULL);
					mciSendString("play shootmusic", NULL, 0, NULL);
					ishoot[1] = 1;
					initialize[1] = 1;
				}
			}
		}
	}
	if (initialize[0] == 1)
	{
		bullet_x[0] = plane_x + 42;
		bullet_y[0] = plane_y - 24;
		initialize[0] = 0;
	}
	if (ishoot[0] == 1)
	{
		putimage(bullet_x[0], bullet_y[0], &mybullet1[0], NOTSRCERASE);
		putimage(bullet_x[0], bullet_y[0], &mybullet2[0], SRCINVERT);
		bullet_y[0] = bullet_y[0] - bullet_v;
	}
	if (bullet_y[0] < 0)
	{
		ishoot[0] = 0;
	}
	if (initialize[1] == 1)
	{
		bullet_x[1] = plane_x + 42;
		bullet_y[1] = plane_y - 24;
		initialize[1] = 0;
	}
	if (ishoot[1] == 1)
	{
		putimage(bullet_x[1], bullet_y[1], &mybullet1[1], NOTSRCERASE);
		putimage(bullet_x[1], bullet_y[1], &mybullet2[1], SRCINVERT);
		bullet_y[1] = bullet_y[1] - bullet_v;
	}
	if (bullet_y[1] < 0)
	{
		ishoot[1] = 0;
	}
	if (enemyexplode[0] == 0)
	{
		if (((bullet_x[0]) < (enemy_x[0] + 104)) && ((bullet_x[0]) > (enemy_x[0] - 19)) && ((bullet_y[0] + bullet_v) > (enemy_y[0] - bullet_v)) && ((bullet_y[0] + bullet_v) < (enemy_y[0] - bullet_v + 148)) && (ishoot[0] == 1))  //玩家子弹打掉敌人飞机
		{
			ishoot[0] = 0;
			enemyexplode[0] = 1;
			++score;
			mciSendString("close scoremusic", NULL, 0, NULL);
			mciSendString("open D:\\gamesourse\\gotEnemy.mp3 alias scoremusic", NULL, 0, NULL);
			mciSendString("play scoremusic", NULL, 0, NULL);
		}
	}
	if (enemyexplode[0] == 1)
	{
		enemy_x[0] = rand() % 487;
		enemy_y[0] = -148;
		enemyexplode[0] = 0;
	}
	if (enemyexplode[1] == 0)
	{
		if (((bullet_x[0]) < (enemy_x[1] + 104)) && ((bullet_x[0]) > (enemy_x[1] - 19)) && ((bullet_y[0] + bullet_v) > (enemy_y[1] - bullet_v)) && ((bullet_y[0] + bullet_v) < (enemy_y[1] - bullet_v + 148)) && (ishoot[0] == 1))  //玩家子弹打掉敌人飞机
		{
			ishoot[0] = 0;
			enemyexplode[1] = 1;
			++score;
			mciSendString("close scoremusic", NULL, 0, NULL);
			mciSendString("open D:\\gamesourse\\gotEnemy.mp3 alias scoremusic", NULL, 0, NULL);
			mciSendString("play scoremusic", NULL, 0, NULL);
		}
	}
	if (enemyexplode[1] == 1)
	{
		enemy_x[1] = rand() % 487;
		enemy_y[1] = -148;
		enemyexplode[1] = 0;
	}
	if (enemyexplode[0] == 0)
	{
		if (((bullet_x[1]) < (enemy_x[0] + 104)) && ((bullet_x[1]) > (enemy_x[0] - 19)) && ((bullet_y[1] + bullet_v) > (enemy_y[0] - bullet_v)) && ((bullet_y[1] + bullet_v) < (enemy_y[0] - bullet_v + 148)) && (ishoot[1] == 1))   //玩家子弹打掉敌人飞机
		{
			ishoot[1] = 0;
			enemyexplode[0] = 1;
			++score;
			mciSendString("close scoremusic", NULL, 0, NULL);
			mciSendString("open D:\\gamesourse\\gotEnemy.mp3 alias scoremusic", NULL, 0, NULL);
			mciSendString("play scoremusic", NULL, 0, NULL);
		}
	}
	if (enemyexplode[0] == 1)
	{
		enemy_x[0] = rand() % 487;
		enemy_y[0] = -148;
		enemyexplode[0] = 0;
	}
	if (enemyexplode[1] == 0)
	{
		if (((bullet_x[1]) < (enemy_x[1] + 104)) && ((bullet_x[1]) > (enemy_x[1] - 19)) && ((bullet_y[1] + bullet_v) > (enemy_y[1] - bullet_v)) && ((bullet_y[1] + bullet_v) < (enemy_y[1] - bullet_v + 148)) && (ishoot[1] == 1))     //玩家子弹打掉敌人飞机
		{
			ishoot[1] = 0;
			enemyexplode[1] = 1;
			++score;
			mciSendString("close scoremusic", NULL, 0, NULL);
			mciSendString("open D:\\gamesourse\\gotEnemy.mp3 alias scoremusic", NULL, 0, NULL);
			mciSendString("play scoremusic", NULL, 0, NULL);
		}
	}
	if (enemyexplode[1] == 1)
	{
		enemy_x[1] = rand() % 487;
		enemy_y[1] = -148;
		enemyexplode[1] = 0;
	}
	if (score==50)       //分数到达50分时，提高游戏难度
	{
		enemy_v =15;
		plane_v = 40;
	}
	if (score==100)     //分数到达100分时，提高游戏难度
	{
		bullet_v = 40;
		enemy_v = 20;
		plane_v = 30;
	}
	if (score==150)     //分数到达150分，提高游戏难度
	{
		enemy_v = 30;
		bullet_v = 50;
		plane_v = 25;
	}
}
void endgame()
{
	if (end==1)                                 
	{
		putimage(plane_x, plane_y, &explode1, NOTSRCERASE);
		putimage(plane_x, plane_y, &explode2, SRCINVERT);
		mciSendString("open D:\\gamesourse\\explode.mp3 alias boommusic", NULL, 0, NULL);
		mciSendString("play boommusic", NULL, 0, NULL);
		putimage(200, 350, &gameover1, NOTSRCERASE);
		putimage(200, 350, &gameover2, SRCINVERT);
		EndBatchDraw();                                           //关闭绘图
		mciSendString("close bkmusic", NULL, 0, NULL);            //关闭游戏背景音乐
		system("pause");
		closegraph();                                             //关闭游戏界面
	}
}
void scorenum()                                                  //显示得分
{
	outtextxy(width*0.48, high*0.95, "得分：");
	char s[5];
	sprintf(s, "%d", score);
	outtextxy(width*0.55, high*0.95, s);
}
int main()
{
	inital();
	while (1)
	{
		BeginBatchDraw();
		putimage(0, 0, &bkphoto);
		scorenum();
		enemy();
		myplane();
		endgame();
		FlushBatchDraw();
		Sleep(100);
	}
	getch();
    return 0;
}

