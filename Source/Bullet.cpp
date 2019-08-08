#include"Bullet.h"

Bullet::Bullet(Point pos, DIR dir, COLORREF color, int damage)
{
	this->pos = pos;
	this->dir = dir;
	this->color = color;
	this->damage = damage;

	speed = 20;

	CalPhysicalSize();
}

bool Bullet::IsExist()
{
	return existing;
}

void Bullet::Destory()
{
	existing = false;
}

void Bullet::Display()
{
	COLORREF fill_color_save = getfillcolor(),
		color_save = getcolor();

	setfillcolor(color);
	setcolor(color);

	fillcircle(pos.x - 1, pos.y - 1, 4);

	setfillcolor(fill_color_save);
	setcolor(color_save);
}

void Bullet::Move()
{
	switch (dir)
	{
	case UP:
		pos.y -= speed;
		CalPhysicalSize();
		if (physical_size.GetStartPoint().y <= 0)
			existing = false;
		break;
	case DOWN:
		pos.y += speed;
		CalPhysicalSize();
		if (physical_size.GetEndPoint().y >= Screen::GetHeight())
			existing = false;
		break;
	case RIGHT:
		pos.x += speed;
		CalPhysicalSize();
		if (physical_size.GetEndPoint().x >= Screen::GetWidth())
			existing = false;
		break;
	case LEFT:
		pos.x -= speed;
		CalPhysicalSize();
		if (physical_size.GetEndPoint().x <= 0)
			existing = false;
		break;
	default:
		break;
	}
}

void Bullet::CalPhysicalSize()
{
	physical_size.SetStartPoint({ pos.x - 2,pos.y - 2 });
	physical_size.SetEndPoint({ pos.x + 2,pos.y + 2 });
}

int Bullet::GetDamage()
{
	return damage;
}