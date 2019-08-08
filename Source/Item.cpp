#include"Item.h"

void Item::CalPhysicalSize()
{
	physical_size.SetStartPoint({ pos.x - 8,pos.y - 8 });
	physical_size.SetEndPoint({ pos.x + 8,pos.y + 8 });
}

void Item::Display()
{
	COLORREF color_save = getfillcolor();
	setfillcolor(color);

	fillrectangle(pos.x - 8, pos.y - 8, pos.x + 8, pos.y + 8);

	setfillcolor(color_save);
}

void Item::SetRandomPos()
{
	int temp = rand() % 5;
	switch (temp)
	{
	case 0:
		pos.x = 150;
		pos.y = 150;
		break;
	case 1:
		pos.x = Screen::GetWidth() - 150;
		pos.y = 150;
		break;
	case 2:
		pos.x = 150;
		pos.y = Screen::GetHeight() - 150;
		break;
	case 3:
		pos.x = Screen::GetWidth() - 150;
		pos.y = Screen::GetHeight() - 150;
		break;
	case 4:
		pos.x = Screen::GetWidth()/2;
		pos.y = Screen::GetHeight()/2;
	default:
		break;
	}
}

void Item::SetRandomFunc()
{
	int temp = rand() % 5;
	func = (Func)temp;

	switch (func)
	{
	case SPEED:
		color = RED;
		break;
	case COOLDOWN:
		color = BLUE;
		break;
	case HEALTH:
		color = GREEN;
		break;
	case POWER:
		color = YELLOW;
		break;
	case SUPERSHOOT:
		color = MAGENTA;
		break;
	default:
		break;
	}
}

bool Item::IsExist()
{
	return existing;
}

void Item::Deploy()
{
	existing = true;
	SetRandomPos();
	CalPhysicalSize();
	SetRandomFunc();
}

void Item::Destory()
{
	existing = false;
}

void Item::Activate(PlayerTank& tank)
{
	switch (func)
	{
	case SPEED:
		if (tank.speed <= 13)
			tank.speed += 1;
		break;
	case COOLDOWN:
		if (tank.cool_down_limit >= 4)tank.cool_down_limit -= 2;
		break;
	case HEALTH:
		tank.hp += 3;
		if (tank.hp >= 15)tank.hp = 15;
		break;
	case POWER:
		if (tank.bullet_power < 4)
			tank.bullet_power++;
	case SUPERSHOOT:
		tank.super_shoot += 10;
	default :
		break;
	}
	Destory();
}