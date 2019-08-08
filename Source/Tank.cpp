#include"Tank.h"

extern Block blocks[BLOCKS];
//<------------------------------PlayerTank------------------------------>
PlayerTank::PlayerTank()
{
	pos.x = SCREEN_WIDTH / 2;
	pos.y = SCREEN_HEIGHT / 2;
	color = GREEN;
	dir = DIR::UP;
	speed = 5;
	hp = 10;
	shoot_cool_down = 0;
	cool_down_limit = 15;
	bullet_power = 1;
	super_shoot = 0;

	CalPhysicalSize();
}

void PlayerTank::SetDir(DIR d)
{
	dir = d;
}

void PlayerTank::SetColor(COLORREF c)
{
	color = c;
}

void PlayerTank::SetPosition(int _x, int _y)
{
	pos.x = _x;
	pos.y = _y;
}

void PlayerTank::DrawTank(DIR d)
{
	fillrectangle(pos.x - 4, pos.y - 4, pos.x + 4, pos.y + 4);
	if (d == DIR::UP || d == DIR::DOWN)
	{
		fillrectangle(pos.x - 8, pos.y - 6, pos.x - 6, pos.y + 6);
		fillrectangle(pos.x + 6, pos.y - 6, pos.x + 8, pos.y + 6);
		if(d==DIR::UP)line(pos.x, pos.y, pos.x, pos.y - 10);
		else line(pos.x, pos.y, pos.x, pos.y + 10);
	}
	else
	{
		fillrectangle(pos.x - 6, pos.y - 8, pos.x + 6, pos.y - 6);
		fillrectangle(pos.x - 6, pos.y + 6, pos.x + 6, pos.y + 8);
		if (d == DIR::RIGHT)line(pos.x, pos.y, pos.x + 10, pos.y);
		else line(pos.x, pos.y, pos.x - 10, pos.y);
	}
}

void PlayerTank::Display()
{
	COLORREF fill_color_save = getfillcolor(),
		color_save = getcolor();

	setfillcolor(color);
	setcolor(color);

	DrawTank(dir);

	setfillcolor(fill_color_save);
	setcolor(color_save);
}

void PlayerTank::Move(DIR d)
{
	if (MoveCheck(d))
	{
		switch (d)
		{
		case UP:
			if (pos.y >= 0 + speed)
				pos.y -= speed;
			break;
		case DOWN:
			if (pos.y <= Screen::GetHeight() - speed)
				pos.y += speed;
			break;
		case RIGHT:
			if (pos.x <= Screen::GetWidth() - speed)
				pos.x += speed;
			break;
		case LEFT:
			if (pos.x >= 0 + speed)
				pos.x -= speed;
			break;
		default:
			break;
		}
	}
	dir = d;

}

void PlayerTank::Shoot(std::list<Bullet*>& lstBullets)
{
	if (shoot_cool_down == 0)
	{
		if (super_shoot <= 0) 
		{
			Bullet* bp = new Bullet(pos, dir, color, bullet_power);
			lstBullets.push_back(bp);
			shoot_cool_down = cool_down_limit;
		}
		else
		{
			Bullet* bp = new Bullet(pos, UP, color, bullet_power);
			lstBullets.push_back(bp);
			bp = new Bullet(pos, DOWN, color, bullet_power);
			lstBullets.push_back(bp);
			bp = new Bullet(pos, LEFT, color, bullet_power);
			lstBullets.push_back(bp);
			bp = new Bullet(pos, RIGHT, color, bullet_power);
			lstBullets.push_back(bp);
			shoot_cool_down = cool_down_limit;
			super_shoot--;
		}
	}
}

void PlayerTank::CoolDown()
{
	if (shoot_cool_down > 0)shoot_cool_down--;
}

bool PlayerTank::IsExist()
{
	return existing;
}

void PlayerTank::Destory()
{
	hp--;
	if (hp <= 0)
		existing = false;
}

void PlayerTank::DestoryByDamage(int damage)
{
	hp -= damage;
	if (hp <= 0)
		existing = false;
}

void PlayerTank::CalPhysicalSize()
{
	if (dir == DOWN || dir == UP)
	{
		physical_size.SetStartPoint({ pos.x - 8,pos.y - 8 });
		physical_size.SetEndPoint({ pos.x + 8,pos.y + 8 });
	}
	else
	{
		physical_size.SetStartPoint({ pos.x - 8,pos.y - 8 });
		physical_size.SetEndPoint({ pos.x + 8,pos.y + 8 });
	}
}

bool PlayerTank::MoveCheck(DIR d)
{
	Rect temp = physical_size;

	switch (d)
	{
	case UP:
		temp.SetStartPoint({ temp.GetStartPoint().x,temp.GetStartPoint().y - speed });
		temp.SetEndPoint({ temp.GetEndPoint().x,temp.GetEndPoint().y - speed });
		break;
	case DOWN:
		temp.SetStartPoint({ temp.GetStartPoint().x,temp.GetStartPoint().y + speed });
		temp.SetEndPoint({ temp.GetEndPoint().x,temp.GetEndPoint().y + speed });
		break;
	case RIGHT:
		temp.SetStartPoint({ temp.GetStartPoint().x + speed,temp.GetStartPoint().y });
		temp.SetEndPoint({ temp.GetEndPoint().x + speed,temp.GetEndPoint().y });
		break;
	case LEFT:
		temp.SetStartPoint({ temp.GetStartPoint().x - speed,temp.GetStartPoint().y });
		temp.SetEndPoint({ temp.GetEndPoint().x - speed,temp.GetEndPoint().y});
		break;
	default:
		break;
	}

	for (int i = 0; i < BLOCKS; i++)
	{
		if (blocks[i].physical_size.CollisionCheck(temp))return false;
	}

	return true;
}