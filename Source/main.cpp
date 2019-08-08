#pragma warning(disable:4996)
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Graphics.h"
#include "Tank.h"
#include "Item.h"
#include "Map.h"
#include <Windows.h>
#include <fstream>

using namespace std;

void GameStart();
void LocalMode();
void ShowStatus();
void GameEnd();
void SetColor();

Status Player1Status, Player2Status;
COLORREF tank1_color, tank2_color;

Block blocks[BLOCKS];

int frame_loop = 100;

int main()
{
	srand((unsigned)time(0));

	SetColor();

	GameStart();

	LocalMode();

	GameEnd();
	return 0;
}

void LocalMode()//local ,two players
{
	PlayerTank tank1, tank2;

	Item item;

	list<Bullet*>bullets;

	//initialization
	tank2.SetColor(tank2_color);
	tank1.SetPosition(400, 100);
	tank1.SetDir(DOWN);
	tank1.SetColor(tank1_color);
	tank2.SetPosition(400, 500);

	Screen::Create();

	Map::Create(blocks);
	
	bool runFlag = true;

	while (runFlag)
	{
		//deploy item
		frame_loop++;
		if (frame_loop == 150) 
		{ 
			item.Deploy(); 
			frame_loop = 0;
		}

		//judge game end
		if (!tank1.IsExist() || !tank2.IsExist())runFlag = false;

		tank1.CoolDown();
		tank2.CoolDown();

		//quit
		if (GetAsyncKeyState('Q'))runFlag = false;

		//player1
		if (GetAsyncKeyState('W'))
			tank1.Move(UP);
		else if (GetAsyncKeyState('S'))
			tank1.Move(DOWN);
		else if (GetAsyncKeyState('A'))
			tank1.Move(LEFT);
		else if (GetAsyncKeyState('D'))
			tank1.Move(RIGHT);


		if (GetAsyncKeyState('J'))
			tank1.Shoot(bullets);

		//player2
		if (GetAsyncKeyState(VK_UP))
			tank2.Move(UP);
		else if (GetAsyncKeyState(VK_DOWN))
			tank2.Move(DOWN);
		else if (GetAsyncKeyState(VK_LEFT))
			tank2.Move(LEFT);
		else if (GetAsyncKeyState(VK_RIGHT))
			tank2.Move(RIGHT);

		if (GetAsyncKeyState(VK_NUMPAD0))
			tank2.Shoot(bullets);

		cleardevice();//clear screen

		//judge collision and display
		Map::Display(blocks);

		tank1.Display();
		tank1.CalPhysicalSize();

		tank2.Display();
		tank2.CalPhysicalSize();

		for (list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++)
		{
			(*it)->Move();

			if (tank1.physical_size.CollisionCheck((*it)->physical_size))
			{
				(*it)->Destory();
				tank1.DestoryByDamage((*it)->GetDamage());
			}

			if (tank2.physical_size.CollisionCheck((*it)->physical_size))
			{
				(*it)->Destory();
				tank2.DestoryByDamage((*it)->GetDamage());
			}

			for(int i=0;i<BLOCKS;i++)
				if(blocks[i].physical_size.CollisionCheck((*it)->physical_size))
				{
					(*it)->Destory();
					break;
				}
		}

		if (tank1.physical_size.CollisionCheck(item.physical_size)
			&&item.IsExist())
			item.Activate(tank1);
		if (tank2.physical_size.CollisionCheck(item.physical_size)
			&&item.IsExist())
			item.Activate(tank2);

		for (list<Bullet*>::iterator it = bullets.begin(); it != bullets.end();)
		{
			if ((*it)->IsExist())
			{
				(*it)->Display();
				it++;
				continue;
			}

			delete* it;
			it = bullets.erase(it);
		}

		if (item.IsExist())item.Display();

		Player1Status.RefreshStatus(tank1);
		Player2Status.RefreshStatus(tank2);

		ShowStatus();

		Sleep(FRAME(15));//sleep a frame
	}

	Screen::Close();

	//release RAM
	for (list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++)
		delete* it;
	bullets.clear();
	
	return;
}


void ShowStatus()
{
	line(800, 0, 800, 600);
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	RECT r = { 800,0,1100,600 };
	char* str = new char[128];

	settextcolor(Player1Status.color);

	sprintf(str, "Player1");
	drawtext((LPCTSTR)str, &r, DT_CENTER);

	r.left += 70;
	r.top += 30;
	sprintf(str, "HP: %d", Player1Status.hp);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Speed: %d", Player1Status.speed);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Cooldown: %d", Player1Status.cool_down_limit);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Next shoot in %d frames", Player1Status.shoot_cool_down);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Bullet can cause %d damage", Player1Status.bullet_power);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "%d super shoots left", Player1Status.super_shoot);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.left -= 70;
	r.top += 30;

	settextcolor(Player2Status.color);

	sprintf(str, "Player2");
	drawtext((LPCTSTR)str, &r, DT_CENTER);

	r.left += 70;
	r.top += 30;
	sprintf(str, "HP: %d", Player2Status.hp);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Speed: %d", Player2Status.speed);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Cooldown: %d", Player2Status.cool_down_limit);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Next shoot in %d frames", Player2Status.shoot_cool_down);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "Bullet can cause %d damage", Player2Status.bullet_power);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	sprintf(str, "%d super shoots left", Player2Status.super_shoot);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;

	settextcolor(WHITE);
	sprintf(str, "Next item in %d frames", 150-frame_loop);
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.left -= 30;
	r.top += 30;
	settextcolor(BLUE);
	sprintf(str, "Blue box will speed up cooldown");
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	settextcolor(RED);
	sprintf(str, "Red box will increase your speed");
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	settextcolor(GREEN);
	sprintf(str, "Green box will health your tank");
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	settextcolor(YELLOW);
	sprintf(str, "Yellow box increase bullet's power");
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	r.top += 30;
	settextcolor(MAGENTA);
	sprintf(str, "Purple box gives you super shoots");
	drawtext((LPCTSTR)str, &r, DT_LEFT);

	delete[] str;
	return;
}

void GameStart()
{
	initgraph(800, 500);
	setbkcolor(0x4F4F4F);
	cleardevice();
	RECT r = { 100,50,700,300 };
	char name[] = "Tank Battle";
	
	LOGFONT f;
	gettextstyle(&f);

	settextcolor(RGB(160, 82, 45));
	settextstyle(90, 50, _T("Consolas"));

	drawtext((LPCTSTR)name, &r, DT_CENTER);

	char* str = new char[128];
	settextstyle(&f);
	settextcolor(WHITE);
	r.top = 240;
	r.left = 50;
	r.right = 750;
	r.bottom = 500;

	sprintf(str, "P1: 'WASD' to move , 'J' to shoot");
	drawtext((LPCTSTR)str, &r, DT_CENTER);
	r.top += 20;
	sprintf(str, "P2: direction key to move , Numpad 0 to shoot");
	drawtext((LPCTSTR)str, &r, DT_CENTER);
	r.top += 30;
	sprintf(str, "To change tank color, please edit 'tank-color.txt'");
	drawtext((LPCTSTR)str, &r, DT_CENTER);

	r.top += 100;
	settextstyle(30, 15, _T("Consolas"));
	settextcolor(RGB(160, 82, 45));
	sprintf(str, "Press 'Enter' to start a local mutiplayer game");
	drawtext((LPCTSTR)str, &r, DT_CENTER);

	bool runflag = true;
	while (runflag)
	{
		if (GetAsyncKeyState(VK_RETURN))
			runflag = false;
	}

	delete[] str;
	return;
}

void GameEnd()
{
	initgraph(800, 500);
	setbkcolor(0x4F4F4F);
	cleardevice();
	RECT r = { 100,100,700,300 };

	LOGFONT f;
	gettextstyle(&f);
	char* str = new char[128];

	settextcolor(RGB(160, 82, 45));
	settextstyle(60, 30, _T("Consolas"));
	int winner;
	if (Player1Status.hp <= Player2Status.hp)winner = 2;
	else winner = 1;
	sprintf(str, "Winner: Player%d",winner);
	drawtext((LPCTSTR)str, &r, DT_CENTER);

	settextstyle(&f);
	settextcolor(WHITE);
	r.top = 240;
	r.left = 50;
	r.right = 750;
	r.bottom = 500;

	sprintf(str, "Thanks for your play!");
	drawtext((LPCTSTR)str, &r, DT_CENTER);
	r.top += 30;
	sprintf(str, "Press 'Enter' quit");
	drawtext((LPCTSTR)str, &r, DT_CENTER);
	
	delete[] str;

	bool runflag = true;
	while (runflag)
	{
		if (GetAsyncKeyState(VK_RETURN))
			runflag = false;
	}

	return;
}


void SetColor()
{
	try
	{
		char e = 'e';
		ifstream fin("tank-color.txt", ios::in);

		if (!fin)throw e;

		int rgb[6];

		for (int i = 0; i < 6; i++)fin >> rgb[i];

		for (int i = 0; i < 6; i++)if (rgb[i] > 255 || rgb[i] < 0)throw e;

		tank1_color = RGB(rgb[0], rgb[1], rgb[2]);
		tank2_color = RGB(rgb[3], rgb[4], rgb[5]);

		fin.close();
	}
	catch (char)
	{
		tank1_color = RGB(35, 235, 185);
		tank2_color = RGB(220, 87, 18);
	}
}